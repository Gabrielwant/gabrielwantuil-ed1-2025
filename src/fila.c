
#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"

typedef struct no { Forma f; struct no* n; } No;
struct fila { No* i; No* f; int n; };
Fila criaFila(void){ struct fila* q=(struct fila*)malloc(sizeof(struct fila)); q->i=NULL;q->f=NULL;q->n=0; return (Fila)q; }
void enfileira(Fila qq, Forma g){ struct fila* q=(struct fila*)qq; No* x=(No*)malloc(sizeof(No)); x->f=g; x->n=NULL; if(!q->f){ q->i=q->f=x; } else { q->f->n=x; q->f=x; } q->n++; }
Forma desenfileira(Fila qq){ struct fila* q=(struct fila*)qq; if(!q->i) return NULL; No* x=q->i; q->i=x->n; if(!q->i) q->f=NULL; Forma f=x->f; free(x); q->n--; return f; }
int filaVazia(Fila qq){ struct fila* q=(struct fila*)qq; return q->i==NULL; }
void destroiFila(Fila qq){ struct fila* q=(struct fila*)qq; while(q->i){ No* x=q->i; q->i=x->n; free(x); } free(q); }
