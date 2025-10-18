#ifndef PILHA_H
#define PILHA_H
#include "formas.h"

typedef struct pilha Pilha;

Pilha *criaPilha(void);
void liberaPilha(Pilha *p);
void push(Pilha *p, Forma *f);
Forma *pop(Pilha *p);
int pilhaVazia(Pilha *p);

#endif
