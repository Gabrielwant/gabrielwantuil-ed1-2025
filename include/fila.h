#ifndef FILA_H
#define FILA_H

typedef struct fila Fila;

Fila *criaFila();
void liberaFila(Fila *f);
int filaVazia(Fila *f);
int insereFila(Fila *f, void *elem);
void *removeFila(Fila *f);
void *frenteFila(Fila *f);
int tamanhoFila(Fila *f);

#endif
