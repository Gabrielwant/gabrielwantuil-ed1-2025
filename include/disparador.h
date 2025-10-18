#ifndef DISPARADOR_H
#define DISPARADOR_H
#include "formas.h"
#include "pilha.h"

typedef struct disparador Disparador;

Disparador *criaDisparador(int id, double x, double y);
void liberaDisparador(Disparador *d);
int atchDisparador(Disparador *d, int carregadorEsq, int carregadorDir);
int shftDisparador(Disparador *d, char lado, int n);
int dspDisparador(Disparador *d, double dx, double dy, char modo);
double getXDisparador(Disparador *d);
double getYDisparador(Disparador *d);

#endif
