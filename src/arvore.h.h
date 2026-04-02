#ifndef ARVORE_H
#define ARVORE_H

#include "mapa.h"

int altura (Mapa *m);

void mostra (Mapa *m);

void percorre_inorder(Mapa* m, funcp f);
void percorre_preorder(Mapa* m, funcp f);
void percorre_posorder(Mapa* m, funcp f);

#endif 