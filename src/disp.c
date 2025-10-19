
#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"

struct carreg { int id; Pilha pilha; };
struct disp { int id; double x; double y; Carreg esq; Carreg dir; Forma fogo; };
Carreg criaCarreg(int id){ struct carreg* c=(struct carreg*)malloc(sizeof(struct carreg)); c->id=id; c->pilha=criaPilha(); return (Carreg)c; }
void destroiCarreg(Carreg cc){ struct carreg* c=(struct carreg*)cc; if(!c) return; destroiPilha(c->pilha); free(c); }
void carregPush(Carreg cc, Forma f){ struct carreg* c=(struct carreg*)cc; empilha(c->pilha,f); }
Forma carregPop(Carreg cc){ struct carreg* c=(struct carreg*)cc; return desempilha(c->pilha); }
int carregVazio(Carreg cc){ struct carreg* c=(struct carreg*)cc; return pilhaVazia(c->pilha); }
Disp criaDisp(int id){ struct disp* d=(struct disp*)malloc(sizeof(struct disp)); d->id=id; d->x=0; d->y=0; d->esq=NULL; d->dir=NULL; d->fogo=NULL; return (Disp)d; }
void destroiDisp(Disp dd){ struct disp* d=(struct disp*)dd; free(d); }
void dispPos(Disp dd,double x,double y){ struct disp* d=(struct disp*)dd; d->x=x; d->y=y; }
void dispLiga(Disp dd, Carreg e, Carreg dir){ struct disp* d=(struct disp*)dd; d->esq=(struct carreg*)e; d->dir=(struct carreg*)dir; }
static void pushL(struct disp* d){ if(d->fogo){ carregPush(d->esq,d->fogo); d->fogo=NULL; } if(!carregVazio(d->dir)) d->fogo=carregPop(d->dir); else d->fogo=NULL; }
static void pushR(struct disp* d){ if(d->fogo){ carregPush(d->dir,d->fogo); d->fogo=NULL; } if(!carregVazio(d->esq)) d->fogo=carregPop(d->esq); else d->fogo=NULL; }
Forma dispShift(Disp dd,char lado){ struct disp* d=(struct disp*)dd; if(lado=='e') pushL(d); else pushR(d); return d->fogo; }
Forma dispFire(Disp dd,double dx,double dy,char modo,double* outx,double* outy){ struct disp* d=(struct disp*)dd; if(!d->fogo) return NULL; double nx=d->x+dx, ny=d->y+dy; *outx=nx; *outy=ny; Forma f=d->fogo; d->fogo=NULL; return f; }
