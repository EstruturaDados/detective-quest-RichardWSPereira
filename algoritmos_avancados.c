#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.

// 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    //
    // - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
    // - Use funções como criarSala(), conectarSalas() e explorarSalas().
    // - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
    // - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
    // - Finalize a exploração com uma opção de saída (s).
    // - Exiba o nome da sala a cada movimento.
    // - Use recursão ou laços para caminhar pela árvore.
    // - Nenhuma inserção dinâmica é necessária neste nível.

// 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
    //
    // - Crie uma struct Pista com campo texto (string).
    // - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
    // - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
    // - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
    // - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
    // - Não precisa remover ou balancear a árvore.
    // - Use funções para modularizar: inserirPista(), listarPistas().
    // - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.

     // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().


// Struct para o mapa da mansão
typedef struct Sala {
    char nome[50];
    struct Sala *esq;
    struct Sala *dir;
} Sala;

// Função com a arvore de pistas
typedef struct Pista {
    char texto[100];
    struct Pista *esq;
    struct Pista *dir;
} Pista;

// Função com a criação das salas com alocação dinamica
Sala* criarSala(const char *nome) {
    Sala *s = malloc(sizeof(Sala));
    strcpy(s->nome, nome);
    s->esq = s->dir = NULL;
    return s;
}

// Função que conecta as salas com seus nós filhos esquerda e direita
void conectarSalas(Sala *s, Sala *e, Sala *d) {
    if (s) { s->esq = e; s->dir = d; }
}

// Cria e insere uma pista na BST
// Nesta função criaremos pistas nos comodas ou nós
Pista* inserirPista(Pista *raiz, const char *texto) {
    if (raiz == NULL) {
        Pista *nova = (Pista*) malloc(sizeof(Pista));
        strcpy(nova->texto, texto);
        nova->esq = NULL;
        nova->dir = NULL;
        return nova;
    }

    if (strcmp(texto, raiz->texto) < 0)
        raiz->esq = inserirPista(raiz->esq, texto);
    else if (strcmp(texto, raiz->texto) > 0)
        raiz->dir = inserirPista(raiz->dir, texto);

    // Se igual, não insere duplicado
    return raiz;
}

// Exibir as pistas em ordem alfabética
void emOrdem(Pista *raiz) {
    if (raiz == NULL) {
        return;
    }
    emOrdem(raiz->esq);
    printf(" %s\n", raiz->texto);
    emOrdem(raiz->dir);
}

// Demonstraremos através dessa função as pistas
void listarPistas(Pista *raiz) {
    if (raiz == NULL) {
        printf("\n Nenhuma pista coletada ainda.\n");
        return;
    }
    printf("\n  Pistas Coletadas\n");
    emOrdem(raiz);
}

// Lista de pistas associadas a um suspeito
typedef struct NoPistaSuspeito {
    char pista[100];
    struct NoPistaSuspeito *prox;
} NoPistaSuspeito;

// Estrutura do suspeito
typedef struct Suspeito {
    char nome[50];
    int contador;                    
    NoPistaSuspeito *pistas;         
    struct Suspeito *prox;           
} Suspeito;

// Tamanho da tabela hash
#define TAM_HASH 10
Suspeito* tabelaHash[TAM_HASH];

// HASHING simples pela soma ASCII do nome
int hashFunc(const char *nome) {
    int soma = 0;
    for (int i = 0; nome[i] != '\0'; i++)
        soma += nome[i];
    return soma % TAM_HASH;
}

// Inicializa hash
void inicializarHash() {
    for (int i = 0; i < TAM_HASH; i++)
        tabelaHash[i] = NULL;
}

// Cria pista dentro da lista do suspeito
void adicionarPistaAoSuspeito(Suspeito *s, const char *p) {
    NoPistaSuspeito *novo = malloc(sizeof(NoPistaSuspeito));
    strcpy(novo->pista, p);
    novo->prox = s->pistas;
    s->pistas = novo;
}

// Busca suspeito dentro da hash
Suspeito* buscarSuspeito(const char *nome) {
    int h = hashFunc(nome);
    Suspeito *atual = tabelaHash[h];
    while (atual) {
        if (strcmp(atual->nome, nome) == 0)
            return atual;
        atual = atual->prox;
    }
    return NULL;
}

// Inserção completa: associa pista → suspeito
void inserirHash(const char *pista, const char *nomeSuspeito) {
    int h = hashFunc(nomeSuspeito);
    Suspeito *buscado = buscarSuspeito(nomeSuspeito);

    // Caso ainda não exista na tabela
    if (!buscado) {
        Suspeito *novo = malloc(sizeof(Suspeito));
        strcpy(novo->nome, nomeSuspeito);
        novo->contador = 1;
        novo->pistas = NULL;
        novo->prox = tabelaHash[h];
        tabelaHash[h] = novo;

        adicionarPistaAoSuspeito(novo, pista);
    }
    else {
        buscado->contador++;
        adicionarPistaAoSuspeito(buscado, pista);
    }
}

// Mostra todos os suspeitos e suas pistas associadas
void listarAssociacoes() {
    printf("\n *** Suspeitos e Suas Pistas ***\n");

    for (int i = 0; i < TAM_HASH; i++) {
        Suspeito *s = tabelaHash[i];
        while (s) {
            printf("\n Suspeito: %s (Quantidades de suspeitas: %d)\n", s->nome, s->contador);
            NoPistaSuspeito *p = s->pistas;
            while (p) {
                printf("   • %s\n", p->pista);
                p = p->prox;
            }
            s = s->prox;
        }
    }
}

// Retorna o suspeito mais citado
Suspeito* suspeitoMaisProvavel() {
    Suspeito *melhor = NULL;

    for (int i = 0; i < TAM_HASH; i++) {
        Suspeito *s = tabelaHash[i];
        while (s) {
            if (!melhor || s->contador > melhor->contador)
                melhor = s;
            s = s->prox;
        }
    }
    return melhor;
}

// Liga pistas específicas a determinados suspeitos
void registrarRelacaoSuspeitos(const char *pista) {

    // Aqui você pode personalizar conforme o quiser
    if (strstr(pista, "diário"))
        inserirHash(pista, "Sr. Alencar");

    if (strstr(pista, "fuligem") || strstr(pista, "fogão"))
        inserirHash(pista, "Cozinheira Rosa");

    if (strstr(pista, "Retrato") || strstr(pista, "rasgado"))
        inserirHash(pista, "Jovem Henrique");

    if (strstr(pista, "Pegadas"))
        inserirHash(pista, "Caseiro Mauro");
}

// Associa salas às pistas coletadas automaticamente
void adicionarPistaDaSala(const char *nomeSala, Pista **arvorePistas) {

    const char *pista = NULL;

    if (strcmp(nomeSala, "Biblioteca") == 0)
        pista = "Página arrancada de um diário antigo";

    else if (strcmp(nomeSala, "Cozinha") == 0)
        pista = "Luvas sujas de fuligem próximas ao fogão";

    else if (strcmp(nomeSala, "Sótão") == 0)
        pista = "Retrato rasgado de um dos suspeitos";

    else if (strcmp(nomeSala, "Quintal") == 0)
        pista = "Pegadas levando em direção ao portão";

    if (pista) {
        printf("📝 Pista encontrada: %s\n", pista);

        *arvorePistas = inserirPista(*arvorePistas, pista);
        registrarRelacaoSuspeitos(pista); 
    }
}

// Função destinada para exploração das salas
void explorarSalas(Sala *atual, Pista **arvorePistas) {
    char opcao;

    while (1) {
        printf("\n Sala atual: **%s**\n", atual->nome);
        printf("Opções:\n");
        printf("  (e) Ir para a esquerda\n");
        printf("  (d) Ir para a direita\n");
        printf("  (p) Ver pistas coletadas\n");
        printf("  (h) Ver suspeitos relacionados (hash)\n");
        printf("  (s) Sair da mansão\n");
        printf("->");
        scanf(" %c", &opcao);

        if (opcao == 's') break;

        else if (opcao == 'p') listarPistas(*arvorePistas);

        else if (opcao == 'h') listarAssociacoes();

        else if (opcao == 'e') {
            if (atual->esq) {
                atual = atual->esq;
                adicionarPistaDaSala(atual->nome, arvorePistas);
            } else printf(" Não existe sala à esquerda.\n");
        }

        else if (opcao == 'd') {
            if (atual->dir) {
                atual = atual->dir;
                adicionarPistaDaSala(atual->nome, arvorePistas);
            } else printf(" Não existe sala à direita.\n");
        }

        else printf(" Comando inválido!\n");
    }
}


int main() {

    inicializarHash();


    // ------- Criando salas -------
    Sala *hall       = criarSala("Hall de Entrada");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *cozinha    = criarSala("Cozinha");
    Sala *salaJantar = criarSala("Sala de Jantar");
    Sala *sotao      = criarSala("Sótão");
    Sala *quintal    = criarSala("Quintal");

    //Conectando salas (árvore fixa)
    conectarSalas(hall, biblioteca, cozinha);
    conectarSalas(biblioteca, sotao, salaJantar);
    conectarSalas(cozinha, NULL, quintal);

    //Árvore de pistas vazia
    Pista *arvorePistas = NULL;

    printf("\nBem-vindo ao Detective Quest\n");
    printf("Explore, colete pistas e encontre o principal suspeito!\n");

    // Começar exploração
    explorarSalas(hall, &arvorePistas);

    // Final do jogo: exibir suspeito mais provável
    Suspeito *prov = suspeitoMaisProvavel();

    printf(" ANÁLISE FINAL DO CASO\n");
    if (prov)
        printf(" O suspeito mais provável é: **%s** (citado %d vezes)\n",
               prov->nome, prov->contador);
    else
        printf("Nenhum suspeito identificado.\n");
    printf("======================================\n");
    return 0;
}

