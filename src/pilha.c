#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef struct no
{
    Forma *f;
    struct no *prox;
} No;

struct pilha
{
    No *topo;
};

Pilha *criaPilha(void)
{
    Pilha *p = malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}

void push(Pilha *p, Forma *f)
{
    No *n = malloc(sizeof(No));
    n->f = f;
    n->prox = p->topo;
    p->topo = n;
}

Forma *pop(Pilha *p)
{
    if (!p || !p->topo)
        return NULL;
    No *n = p->topo;
    Forma *f = n->f;
    p->topo = n->prox;
    free(n);
    return f;
}

int pilhaVazia(Pilha *p)
{
    return !p || p->topo == NULL;
}

void liberaPilha(Pilha *p)
{
    while (!pilhaVazia(p))
    {
        Forma *f = pop(p);
        if (f)
            liberaForma(f);
    }
    free(p);
}
