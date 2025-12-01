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
    Sala *s = (Sala*) malloc(sizeof(Sala));
    strcpy(s->nome, nome);
    s->esq = NULL;
    s->dir = NULL;
    return s;
}

// Função que conecta as salas com seus nós filhos esquerda e direita
void conectarSalas(Sala *s, Sala *e, Sala *d) {
    if (s) {
        s->esq = e;
        s->dir = d;
    }
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
    if (raiz == NULL) return;
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


// Associa salas às pistas coletadas automaticamente
void adicionarPistaDaSala(const char *nomeSala, Pista **arvorePistas) {
    if (strcmp(nomeSala, "Biblioteca") == 0) {
        *arvorePistas = inserirPista(*arvorePistas, 
            "Página arrancada de um diário antigo");
        printf(" Você encontrou uma pista na Biblioteca!\n");
    }
    else if (strcmp(nomeSala, "Cozinha") == 0) {
        *arvorePistas = inserirPista(*arvorePistas, 
            "Luvas sujas de fuligem próximas ao fogão");
        printf(" Você encontrou uma pista na Cozinha!\n");
    }
    else if (strcmp(nomeSala, "Sótão") == 0) {
        *arvorePistas = inserirPista(*arvorePistas, 
            "Retrato rasgado de um dos suspeitos");
        printf(" Você encontrou uma pista no Sótão!\n");
    }
    else if (strcmp(nomeSala, "Quintal") == 0) {
        *arvorePistas = inserirPista(*arvorePistas, 
            "Pegadas levando em direção ao portão");
        printf(" Você encontrou uma pista no Quintal!\n");
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
        printf("  (s) Sair da exploração\n");
        printf("→ ");
        scanf(" %c", &opcao);

        if (opcao == 's') {
            printf("\n Você encerrou a exploração.\n");
            break;
        }
        else if (opcao == 'p') {
            listarPistas(*arvorePistas);
        }
        else if (opcao == 'e') {
            if (atual->esq) {
                atual = atual->esq;
                adicionarPistaDaSala(atual->nome, arvorePistas);
            } else {
                printf("Não existe sala à esquerda!\n");
            }
        }
        else if (opcao == 'd') {
            if (atual->dir) {
                atual = atual->dir;
                adicionarPistaDaSala(atual->nome, arvorePistas);
            } else {
                printf("Não existe sala à direita!\n");
            }
        }
        else {
            printf("Comando inválido.\n");
        }
    }
}


int main() {
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

    printf("\nBem-vindo ao Detective Quest – Nível Aventureiro!\n");
    printf("Explore a mansão e descubra novas pistas!\n");

    // Começar exploração
    explorarSalas(hall, &arvorePistas);

    return 0;
}

