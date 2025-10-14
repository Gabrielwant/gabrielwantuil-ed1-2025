#ifndef FILA_H
#define FILA_H
typedef struct fila Fila;
Fila* criaFila();
void liberaFila(Fila* f);
int filaVazia(Fila* f);
int filaEnqueue(Fila* f, void* elem);
void* filaDequeue(Fila* f);
void* filaPrimeiro(Fila* f);
#endif
