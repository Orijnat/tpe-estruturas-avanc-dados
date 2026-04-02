#ifndef ARVORE_H
#define ARVORE_H

#include "mapa.h"

int altura (No *m);

void mostra (No *m);

void percorre_inorder(No* m, funcp f);
void percorre_preorder(No* m, funcp f);
void percorre_posorder(No* m, funcp f);

#endif 