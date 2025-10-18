#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disparador.h"

struct disparador
{
    int id;
    double x, y;
    Pilha *esq;
    Pilha *dir;
    Forma *atual;
};

Disparador *criaDisparador(int id, double x, double y)
{
    Disparador *d = malloc(sizeof(Disparador));
    d->id = id;
    d->x = x;
    d->y = y;
    d->esq = criaPilha();
    d->dir = criaPilha();
    d->atual = NULL;
    return d;
}

void liberaDisparador(Disparador *d)
{
    if (!d)
        return;
    if (d->atual)
        liberaForma(d->atual);
    liberaPilha(d->esq);
    liberaPilha(d->dir);
    free(d);
}

int atchDisparador(Disparador *d, int carregadorEsq, int carregadorDir)
{
    if (!d)
        return 0;
    for (int i = 0; i < carregadorEsq; i++)
    {
        char cor[20];
        sprintf(cor, "E%d", i);
        push(d->esq, criaCirculo(i, d->x - 10 * i, d->y, 5, "black", cor));
    }
    for (int i = 0; i < carregadorDir; i++)
    {
        char cor[20];
        sprintf(cor, "D%d", i);
        push(d->dir, criaRetangulo(i, d->x + 10 * i, d->y, 8, 8, "black", cor));
    }
    d->atual = pop(d->dir);
    return 1;
}

int shftDisparador(Disparador *d, char lado, int n)
{
    if (!d)
        return 0;

    for (int i = 0; i < n; i++)
    {
        if (lado == 'e' || lado == 'E')
        {
            if (d->atual)
                push(d->esq, d->atual);
            d->atual = pop(d->dir);
        }
        else if (lado == 'd' || lado == 'D')
        {
            if (d->atual)
                push(d->dir, d->atual);
            d->atual = pop(d->esq);
        }
    }
    return 1;
}

int dspDisparador(Disparador *d, double dx, double dy, char modo)
{
    if (!d)
        return 0;
    if (!d->atual)
        return 0;

    d->x += dx;
    d->y += dy;
    if (modo == 'A')
        printf("Disparo alternado.\n");
    else if (modo == 'B')
        printf("Disparo duplo.\n");
    else
        printf("Disparo simples.\n");
    return 1;
}

double getXDisparador(Disparador *d)
{
    return d ? d->x : 0;
}

double getYDisparador(Disparador *d)
{
    return d ? d->y : 0;
}
