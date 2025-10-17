#include <stdio.h>
#include <stdlib.h>
#include "disparador.h"

struct disparador
{
    int id;
    double x, y;
    int carregadorEsq;
    int carregadorDir;
};

Disparador *criaDisparador(int id, double x, double y)
{
    Disparador *d = malloc(sizeof(Disparador));
    if (!d)
        return NULL;
    d->id = id;
    d->x = x;
    d->y = y;
    d->carregadorEsq = -1;
    d->carregadorDir = -1;
    return d;
}

void liberaDisparador(Disparador *d)
{
    free(d);
}

int atchDisparador(Disparador *d, int carregadorEsq, int carregadorDir)
{
    if (!d)
        return 0;
    d->carregadorEsq = carregadorEsq;
    d->carregadorDir = carregadorDir;
    return 1;
}

int shftDisparador(Disparador *d, char lado, int n)
{
    if (!d)
        return 0;
    if (lado == 'D' || lado == 'd')
        d->x += 10 * n;
    else if (lado == 'E' || lado == 'e')
        d->x -= 10 * n;
    else if (lado == 'C' || lado == 'c')
        d->y -= 10 * n;
    else if (lado == 'B' || lado == 'b')
        d->y += 10 * n;
    return 1;
}

int dspDisparador(Disparador *d, double dx, double dy, char modo)
{
    if (!d)
        return 0;
    d->x += dx;
    d->y += dy;
    printf("Disparo modo %c realizado para (%.2f, %.2f)\n", modo, d->x, d->y);
    return 1;
}
