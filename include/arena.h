#ifndef ARENA_H
#define ARENA_H
#include "formas.h"
#include <stdio.h>

typedef struct arena Arena;

Arena *criaArena(void);
void adicionaFormaArena(Arena *a, Forma *f);
void processaSobreposicoes(Arena *a);
void escreveArenaSVG(Arena *a, FILE *svg);
double getPontuacao(Arena *a);
void liberaArena(Arena *a);

#endif
