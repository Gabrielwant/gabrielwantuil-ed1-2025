#include <stdlib.h>
#include "disparador.h"
struct disparador {
    int id;
    double x;
    double y;
    int carregadorEsq;
    int carregadorDir;
    void* posDisparo;
};
Disparador* criaDisparador(int id, double x, double y){
    Disparador* d = malloc(sizeof(Disparador));
    if(!d) return NULL;
    d->id = id;
    d->x = x;
    d->y = y;
    d->carregadorEsq = -1;
    d->carregadorDir = -1;
    d->posDisparo = NULL;
    return d;
}
void liberaDisparador(Disparador* d){
    if(!d) return;
    free(d);
}
int atchDisparador(Disparador* d, int carregadorEsq, int carregadorDir){
    if(!d) return 0;
    d->carregadorEsq = carregadorEsq;
    d->carregadorDir = carregadorDir;
    return 1;
}
int shftDisparador(Disparador* d, char lado, int n){
    (void)d; (void)lado; (void)n;
    return 1;
}
int dspDisparador(Disparador* d, double dx, double dy, char modo){
    (void)d; (void)dx; (void)dy; (void)modo;
    return 1;
}
