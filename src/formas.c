
#include <stdio.h>
#include <stdlib.h>
#include "formas.h"
#include "util.h"

typedef struct item { int tipo; int id; double x; double y; double w; double h; double r; double x2; double y2; char cb[32]; char cp[32]; char txt[256]; char anc; } Item;
struct banco { Item* v; int n; int cap; int maxId; };

static void garante(struct banco* b){ if(b->n<b->cap) return; int nv=b->cap==0?64:b->cap*2; Item* x=(Item*)malloc(nv*sizeof(Item)); for(int i=0;i<b->n;i++) x[i]=b->v[i]; if(b->v) free(b->v); b->v=x; b->cap=nv; }
Banco criaBanco(void){ struct banco* b=(struct banco*)malloc(sizeof(struct banco)); if(!b) return NULL; b->v=NULL;b->n=0;b->cap=0;b->maxId=0; return b; }
void destroiBanco(Banco bb){ struct banco* b=(struct banco*)bb; if(!b) return; if(b->v) free(b->v); free(b); }
int bancoInsereCirculo(Banco bb,int id,double x,double y,double r,const char* corb,const char* corp){ struct banco* b=(struct banco*)bb; garante(b); Item it; it.tipo=1; it.id=id; if(id>b->maxId) b->maxId=id; it.x=x;it.y=y;it.r=r;it.w=0;it.h=0;it.x2=0;it.y2=0; it.anc='i'; util_copy(it.cb,corb,31); util_copy(it.cp,corp,31); it.txt[0]=0; b->v[b->n++]=it; return 1; }
int bancoInsereRetangulo(Banco bb,int id,double x,double y,double w,double h,const char* corb,const char* corp){ struct banco* b=(struct banco*)bb; garante(b); Item it; it.tipo=2; it.id=id; if(id>b->maxId) b->maxId=id; it.x=x;it.y=y;it.w=w;it.h=h;it.r=0;it.x2=0;it.y2=0; it.anc='i'; util_copy(it.cb,corb,31); util_copy(it.cp,corp,31); it.txt[0]=0; b->v[b->n++]=it; return 1; }
int bancoInsereLinha(Banco bb,int id,double x1,double y1,double x2,double y2,const char* cor){ struct banco* b=(struct banco*)bb; garante(b); Item it; it.tipo=3; it.id=id; if(id>b->maxId) b->maxId=id; it.x=x1;it.y=y1;it.x2=x2;it.y2=y2;it.w=0;it.h=0;it.r=0; it.anc='i'; util_copy(it.cb,cor,31); it.cp[0]=0; it.txt[0]=0; b->v[b->n++]=it; return 1; }
int bancoInsereTexto(Banco bb,int id,double x,double y,char ancora,const char* corb,const char* corp,const char* txt){ struct banco* b=(struct banco*)bb; garante(b); Item it; it.tipo=4; it.id=id; if(id>b->maxId) b->maxId=id; it.x=x;it.y=y;it.w=0;it.h=0;it.r=0;it.x2=0;it.y2=0; it.anc=ancora; util_copy(it.cb,corb,31); util_copy(it.cp,corp,31); util_copy(it.txt,txt,255); b->v[b->n++]=it; return 1; }
int bancoQuantidade(Banco bb){ struct banco* b=(struct banco*)bb; return b?b->n:0; }
Forma bancoGet(Banco bb,int i){ struct banco* b=(struct banco*)bb; if(!b) return NULL; if(i<0||i>=b->n) return NULL; return (Forma)&b->v[i]; }
void bancoRemovePrimeiros(Banco bb,int n){ struct banco* b=(struct banco*)bb; if(!b) return; if(n<=0) return; if(n>=b->n){ b->n=0; return; } for(int i=0;i<b->n-n;i++) b->v[i]=b->v[i+n]; b->n-=n; }
void bancoInsereNoChao(Banco bb, Forma f){ struct banco* b=(struct banco*)bb; if(!b||!f) return; garante(b); b->v[b->n++]=*(Item*)f; if(((Item*)f)->id>b->maxId) b->maxId=((Item*)f)->id; }
int formaTipo(Forma f){ return f?((Item*)f)->tipo:0; }
int formaId(Forma f){ return f?((Item*)f)->id:0; }
double formaX(Forma f){ return f?((Item*)f)->x:0; }
double formaY(Forma f){ return f?((Item*)f)->y:0; }
double formaW(Forma f){ return f?((Item*)f)->w:0; }
double formaH(Forma f){ return f?((Item*)f)->h:0; }
double formaR(Forma f){ return f?((Item*)f)->r:0; }
double formaX2(Forma f){ return f?((Item*)f)->x2:0; }
double formaY2(Forma f){ return f?((Item*)f)->y2:0; }
const char* formaCorB(Forma f){ return f?((Item*)f)->cb:NULL; }
const char* formaCorP(Forma f){ return f?((Item*)f)->cp:NULL; }
const char* formaTxt(Forma f){ return f?((Item*)f)->txt:NULL; }
char formaAnc(Forma f){ return f?((Item*)f)->anc:'i'; }
Forma formaClona(Forma f,int novoIdTrocaCores){ Item* it=(Item*)f; Item* c=(Item*)malloc(sizeof(Item)); *c=*it; if(novoIdTrocaCores){ char aux[32]; util_copy(aux,c->cb,31); util_copy(c->cb,c->cp,31); util_copy(c->cp,aux,31); } return (Forma)c; }
void formaSetPos(Forma f,double x,double y){ Item* it=(Item*)f; it->x=x; it->y=y; }
void formaSetCorB(Forma f,const char* c){ Item* it=(Item*)f; util_copy(it->cb,c,31); }
void formaSetCorP(Forma f,const char* c){ Item* it=(Item*)f; util_copy(it->cp,c,31); }
double formaArea(Forma f){ Item* it=(Item*)f; if(it->tipo==1) return 3.141592653589793*it->r*it->r; if(it->tipo==2) return util_fabs(it->w*it->h); if(it->tipo==3){ double dx=it->x2-it->x; double dy=it->y2-it->y; double L=util_sqrt(dx*dx+dy*dy); return 2.0*L; } if(it->tipo==4){ int n=util_strlen(it->txt); return 20.0*n; } return 0; }
Forma formaDup(Forma f){ Item* it=(Item*)f; Item* d=(Item*)malloc(sizeof(Item)); *d=*it; return (Forma)d; }
