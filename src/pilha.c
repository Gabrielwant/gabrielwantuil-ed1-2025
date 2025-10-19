
#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"

typedef struct no { Forma f; struct no* n; } No;
struct pilha { No* t; int n; };
Pilha criaPilha(void){ struct pilha* p=(struct pilha*)malloc(sizeof(struct pilha)); p->t=NULL;p->n=0; return (Pilha)p; }
void empilha(Pilha pp, Forma f){ struct pilha* p=(struct pilha*)pp; No* x=(No*)malloc(sizeof(No)); x->f=f; x->n=p->t; p->t=x; p->n++; }
Forma desempilha(Pilha pp){ struct pilha* p=(struct pilha*)pp; if(!p->t) return NULL; No* x=p->t; p->t=x->n; Forma f=x->f; free(x); p->n--; return f; }
int pilhaVazia(Pilha pp){ struct pilha* p=(struct pilha*)pp; return p->t==NULL; }
void destroiPilha(Pilha pp){ struct pilha* p=(struct pilha*)pp; while(p->t){ No* x=p->t; p->t=x->n; free(x); } free(p); }
