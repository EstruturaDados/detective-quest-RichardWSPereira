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



// ------------------ STRUCT DA SALA ------------------
typedef struct Sala {
    char nome[50];
    struct Sala *esq;
    struct Sala *dir;
} Sala;

// ------------------ FUNÇÕES ------------------

// Cria uma nova sala
Sala* criarSala(const char *nome) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome); // comando que nomeia os nós
    nova->esq = NULL; // Inicialmente estão vazios
    nova->dir = NULL; // Inicialmente estão vazios
    return nova;
}

// Conecta duas salas como esquerda e direita
// Após a criação agora atribuimos os nós filhos ao nó raiz
void conectarSalas(Sala *sala, Sala *esq, Sala *dir) {
    if (sala != NULL) {
        sala->esq = esq;
        sala->dir = dir;
    }
}

// Exploração da árvore da mansão
void explorarSalas(Sala *atual) {
    char opcao;

    while (1) {
        printf("\n Você está na sala: **%s**\n", atual->nome);
        printf("Escolha o caminho:\n");
        printf("  (e) Ir para a esquerda\n");
        printf("  (d) Ir para a direita\n");
        printf("  (s) Sair da exploração\n");
        printf("->");
        scanf(" %c", &opcao);

        if (opcao == 's') {
            printf("\n Você decidiu encerrar a exploração.\n");
            break;
        } 
        else if (opcao == 'e') {
            if (atual->esq != NULL)
                atual = atual->esq;
            else
                printf(" Não existe sala à esquerda!\n");
        } 
        else if (opcao == 'd') {
            if (atual->dir != NULL)
                atual = atual->dir;
            else
                printf(" Não existe sala à direita!\n");
        }
        else {
            printf(" Opção inválida. Tente novamente.\n");
        }
    }
}

// ------------------ MAIN ------------------
int main() {

    // Criação das salas da mansão
    Sala *hall       = criarSala("Hall de Entrada");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *cozinha    = criarSala("Cozinha");
    Sala *salaJantar = criarSala("Sala de Jantar");
    Sala *sotao      = criarSala("Sótão");
    Sala *quintal    = criarSala("Quintal");

    /*
            Hall de Entrada
             /            \
      Biblioteca         Cozinha
        /     \           /     \
    Sótão  Sala Jantar  NULL   Quintal
    */

    // Chamadas das funções que conectam os comodos com sendo esquerda e direita com o no raiz 
    
    conectarSalas(hall, biblioteca, cozinha);
    conectarSalas(biblioteca, sotao, salaJantar);
    conectarSalas(cozinha, NULL, quintal);

    // Inicia exploração
    explorarSalas(hall);

    return 0;
}


