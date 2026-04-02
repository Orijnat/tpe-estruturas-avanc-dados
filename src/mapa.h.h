#ifndef MAPA_H
#define MAPA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int id;
    char nome[50];
    float preco;
} Produto;

typedef struct no {
    Produto produto;
    struct no *esq;
    struct no *dir;
} No;

No* cria_no(Produto p);
void destroi_arvore(No* raiz);

int id_existe(No* raiz, int id);
No* insere_por_id(No* raiz, Produto p);
No* insere_por_preco(No* raiz, Produto p);
void inserir_sincronizado(No** raizID, No** raizPreco, Produto p);

Produto* busca_por_id(No* raiz, int id);
void busca_por_faixa_preco(No* raiz, float min, float max);
No* vizinho_mais_proximo(No* raiz, float alvo, No* melhor);

No* min_valor_no(No* no);
No* remover_no_id(No* raiz, int id);
No* remover_no_preco(No* raiz, float preco, int id);
void remover_sincronizado(No** raizID, No** raizPreco, int id);

#endif