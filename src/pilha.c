#include <stdlib.h>
#include "pilha.h"

struct pilha
{
    int topo;
    int capacidade;
    void **dados;
};

Pilha *criaPilha()
{
    Pilha *p = malloc(sizeof(Pilha));
    if (!p)
        return NULL;
    p->capacidade = 10;
    p->topo = 0;
    p->dados = malloc(sizeof(void *) * p->capacidade);
    if (!p->dados)
    {
        free(p);
        return NULL;
    }
    return p;
}

void liberaPilha(Pilha *p)
{
    if (!p)
        return;
    free(p->dados);
    free(p);
}

int pilhaVazia(Pilha *p)
{
    return p == NULL || p->topo == 0;
}

int pilhaPush(Pilha *p, void *elem)
{
    if (!p)
        return 0;
    if (p->topo == p->capacidade)
    {
        int novaCap = p->capacidade * 2;
        void **novo = realloc(p->dados, sizeof(void *) * novaCap);
        if (!novo)
            return 0;
        p->dados = novo;
        p->capacidade = novaCap;
    }
    p->dados[p->topo++] = elem;
    return 1;
}

void *pilhaPop(Pilha *p)
{
    if (!p || p->topo == 0)
        return NULL;
    return p->dados[--p->topo];
}

void *pilhaTopo(Pilha *p)
{
    if (!p || p->topo == 0)
        return NULL;
    return p->dados[p->topo - 1];
}

int tamanhoPilha(Pilha *p)
{
    if (!p)
        return 0;
    return p->topo;
}
