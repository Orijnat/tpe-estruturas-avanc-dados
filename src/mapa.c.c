#include "mapa.h"

No* cria_no(Produto p) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo) {
        novo->produto = p;
        novo->esq = novo->dir = NULL;
    }
    return novo;
}

int id_existe(No* raiz, int id) {
    if (raiz == NULL) return 0;
    if (id == raiz->produto.id) return 1;
    if (id < raiz->produto.id) return id_existe(raiz->esq, id);
    return id_existe(raiz->dir, id);
}

No* insere_por_id(No* raiz, Produto p) {
    if (raiz == NULL) return cria_no(p);
    if (p.id < raiz->produto.id) raiz->esq = insere_por_id(raiz->esq, p);
    else if (p.id > raiz->produto.id) raiz->dir = insere_por_id(raiz->dir, p);
    return raiz;
}

No* insere_por_preco(No* raiz, Produto p) {
    if (raiz == NULL) return cria_no(p);
    if (p.preco < raiz->produto.preco) raiz->esq = insere_por_preco(raiz->esq, p);
    else raiz->dir = insere_por_preco(raiz->dir, p);
    return raiz;
}

void inserir_sincronizado(No** raizID, No** raizPreco, Produto p) {
    if (id_existe(*raizID, p.id)) {
        printf("Erro: O ID %d ja existe!\n", p.id);
        return;
    }
    *raizID = insere_por_id(*raizID, p);
    *raizPreco = insere_por_preco(*raizPreco, p);
    printf("Produto '%s' inserido com ID %d.\n", p.nome, p.id);
}

Produto* busca_por_id(No* raiz, int id) {
    if (raiz == NULL) return NULL;
    if (id == raiz->produto.id) return &(raiz->produto);
    return (id < raiz->produto.id) ? busca_por_id(raiz->esq, id) : busca_por_id(raiz->dir, id);
}

void busca_por_faixa_preco(No* raiz, float min, float max) {
    if (raiz == NULL) return;
    if (raiz->produto.preco > min) busca_por_faixa_preco(raiz->esq, min, max);
    if (raiz->produto.preco >= min && raiz->produto.preco <= max)
        printf("ID: %d | %s | R$ %.2f\n", raiz->produto.id, raiz->produto.nome, raiz->produto.preco);
    if (raiz->produto.preco < max) busca_por_faixa_preco(raiz->dir, min, max);
}

No* vizinho_mais_proximo(No* raiz, float alvo, No* melhor) {
    if (raiz == NULL) return melhor;
    if (melhor == NULL || fabs(raiz->produto.preco - alvo) < fabs(melhor->produto.preco - alvo))
        melhor = raiz;
    if (alvo < raiz->produto.preco) return vizinho_mais_proximo(raiz->esq, alvo, melhor);
    return vizinho_mais_proximo(raiz->dir, alvo, melhor);
}

No* min_valor_no(No* no) {
    No* atual = no;
    while (atual && atual->esq != NULL) atual = atual->esq;
    return atual;
}

No* remover_no_id(No* raiz, int id) {
    if (raiz == NULL) return NULL;
    if (id < raiz->produto.id) raiz->esq = remover_no_id(raiz->esq, id);
    else if (id > raiz->produto.id) raiz->dir = remover_no_id(raiz->dir, id);
    else {
        if (raiz->esq == NULL) { No* t = raiz->dir; free(raiz); return t; }
        else if (raiz->dir == NULL) { No* t = raiz->esq; free(raiz); return t; }
        No* t = min_valor_no(raiz->dir);
        raiz->produto = t->produto;
        raiz->dir = remover_no_id(raiz->dir, t->produto.id);
    }
    return raiz;
}

No* remover_no_preco(No* raiz, float preco, int id) {
    if (raiz == NULL) return NULL;
    if (preco < raiz->produto.preco) raiz->esq = remover_no_preco(raiz->esq, preco, id);
    else if (preco > raiz->produto.preco) raiz->dir = remover_no_preco(raiz->dir, preco, id);
    else if (id != raiz->produto.id) raiz->dir = remover_no_preco(raiz->dir, preco, id);
    else {
        if (raiz->esq == NULL) { No* t = raiz->dir; free(raiz); return t; }
        else if (raiz->dir == NULL) { No* t = raiz->esq; free(raiz); return t; }
        No* t = min_valor_no(raiz->dir);
        raiz->produto = t->produto;
        raiz->dir = remover_no_preco(raiz->dir, t->produto.preco, t->produto.id);
    }
    return raiz;
}

void remover_sincronizado(No** raizID, No** raizPreco, int id) {
    Produto* p = busca_por_id(*raizID, id);
    if (p) {
        float preco_antigo = p->preco;
        *raizID = remover_no_id(*raizID, id);
        *raizPreco = remover_no_preco(*raizPreco, preco_antigo, id);
        printf("Produto ID %d removido com sucesso.\n", id);
    } else {
        printf("Erro: Produto ID %d nao encontrado.\n", id);
    }
}

void destroi_arvore(No* raiz) {
    if (raiz) {
        destroi_arvore(raiz->esq);
        destroi_arvore(raiz->dir);
        free(raiz);
    }
}