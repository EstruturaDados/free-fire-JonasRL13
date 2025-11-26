//desafio free fire - novato

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10
#define MAX_NOME 30
#define MAX_TIPO 20

typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} Item;

Item mochila[MAX_ITENS];
int total = 0;

/* Remove newline deixado pelo fgets */
void trim_newline(char *s) {
    size_t n = strlen(s);
    if (n > 0 && s[n-1] == '\n') s[n-1] = '\0';
}

/* Lista todos os itens */
void listarItens() {
    if (total == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    printf("\nItens na mochila (%d):\n", total);
    for (int i = 0; i < total; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n", i+1,
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

/* Busca sequencial por nome; retorna índice ou -1 */
int buscarItemPorNome(const char *nome) {
    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

/* Insere um item (até MAX_ITENS) */
void inserirItem() {
    if (total >= MAX_ITENS) {
        printf("Mochila cheia. Remova um item antes de inserir.\n");
        return;
    }
    Item novo;
    printf("Digite o nome do item: ");
    fgets(novo.nome, MAX_NOME, stdin);
    trim_newline(novo.nome);
    if (strlen(novo.nome) == 0) {
        printf("Nome inválido.\n");
        return;
    }

    printf("Digite o tipo do item (arma/municao/cura/etc): ");
    fgets(novo.tipo, MAX_TIPO, stdin);
    trim_newline(novo.tipo);
    if (strlen(novo.tipo) == 0) strcpy(novo.tipo, "desconhecido");

    printf("Digite a quantidade: ");
    if (scanf("%d", &novo.quantidade) != 1) {
        printf("Quantidade inválida.\n");
        int c; while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    int c; while ((c = getchar()) != '\n' && c != EOF); // limpar buffer

    int idx = buscarItemPorNome(novo.nome);
    if (idx != -1) {
        mochila[idx].quantidade += novo.quantidade;
        printf("Item já existia. Quantidade atualizada: %d\n", mochila[idx].quantidade);
    } else {
        mochila[total++] = novo;
        printf("Item inserido com sucesso.\n");
    }
}

/* Remove item por nome */
void removerItem() {
    char nome[MAX_NOME];
    printf("Digite o nome do item a remover: ");
    fgets(nome, MAX_NOME, stdin);
    trim_newline(nome);
    int idx = buscarItemPorNome(nome);
    if (idx == -1) {
        printf("Item não encontrado.\n");
        return;
    }
    for (int i = idx; i < total - 1; i++) {
        mochila[i] = mochila[i+1];
    }
    total--;
    printf("Item removido com sucesso.\n");
}

/* Busca e exibe dados do item */
void buscarItem() {
    char nome[MAX_NOME];
    printf("Digite o nome do item a buscar: ");
    fgets(nome, MAX_NOME, stdin);
    trim_newline(nome);
    int idx = buscarItemPorNome(nome);
    if (idx == -1) {
        printf("Item não encontrado.\n");
    } else {
        printf("Item encontrado: Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[idx].nome, mochila[idx].tipo, mochila[idx].quantidade);
    }
}

int menu() {
    printf("\n=== DESAFIO FREE FIRE - MENU (Nível Novato) ===\n");
    printf("1 - Inserir item\n");
    printf("2 - Remover item por nome\n");
    printf("3 - Listar itens\n");
    printf("4 - Buscar item por nome\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
    int op;
    if (scanf("%d", &op) != 1) {
        int c; while ((c = getchar()) != '\n' && c != EOF);
        return -1;
    }
    int c; while ((c = getchar()) != '\n' && c != EOF);
    return op;
}

int main() {
    int opcao;
    printf("Bem-vindo ao Desafio Free Fire - Nível Novato.\n");
    do {
        opcao = menu();
        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: buscarItem(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida.\n"); break;
        }
    } while (opcao != 0);
    return 0;
}
