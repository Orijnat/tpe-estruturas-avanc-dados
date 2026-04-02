#include <stdio.h>
#include "mapa.h"

int proximo_id = 1;

void menu() {
    printf("1. Inserir Produto\n");
    printf("2. Buscar por ID\n");
    printf("3. Listar por Faixa de Preco\n");
    printf("4. Preco mais Proximo (Nearest Neighbor)\n");
    printf("5. Remover Produto\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

int main() {
    No *raizID = NULL, *raizPreco = NULL;
    int opcao, id;
    float v1, v2;
    Produto p;

    do {
        menu();
        if (scanf("%d", &opcao) != 1) break;

        switch(opcao) {
            case 1:
                p.id = proximo_id++;
                printf("Nome: "); scanf(" %[^\n]s", p.nome);
                printf("Preco: "); scanf("%f", &p.preco);
                inserir_sincronizado(&raizID, &raizPreco, p);
                break;
            case 2:
                printf("ID: "); scanf("%d", &id);
                Produto* r = busca_por_id(raizID, id);
                if(r) printf("-> %s (R$ %.2f)\n", r->nome, r->preco);
                else printf("Nao encontrado.\n");
                break;
            case 3:
                printf("Min: "); scanf("%f", &v1);
                printf("Max: "); scanf("%f", &v2);
                busca_por_faixa_preco(raizPreco, v1, v2);
                break;
            case 4:
                printf("Alvo: "); scanf("%f", &v1);
                No* viz = vizinho_mais_proximo(raizPreco, v1, NULL);
                if(viz) printf("Mais proximo: %s (R$ %.2f)\n", viz->produto.nome, viz->produto.preco);
                break;
            case 5:
                printf("ID para remover: "); scanf("%d", &id);
                remover_sincronizado(&raizID, &raizPreco, id);
                break;
        }
    } while(opcao != 0);

    destroi_arvore(raizID);
    destroi_arvore(raizPreco);
    return 0;
}