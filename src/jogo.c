
#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include "formas.h"
#include "geom.h"
#include "util.h"

typedef struct lan { Forma f; double x; double y; } Lan;
struct arena { Lan* v; int n; int cap; };
static void a_gar(struct arena* a){ if(a->n<a->cap) return; int nv=a->cap==0?64:a->cap*2; Lan* x=(Lan*)malloc(nv*sizeof(Lan)); for(int i=0;i<a->n;i++) x[i]=a->v[i]; if(a->v) free(a->v); a->v=x; a->cap=nv; }
Arena criaArena(void){ struct arena* a=(struct arena*)malloc(sizeof(struct arena)); a->v=NULL;a->n=0;a->cap=0; return (Arena)a; }
void destroiArena(Arena aa){ struct arena* a=(struct arena*)aa; if(a->v) free(a->v); free(a); }
void arenaLanca(Arena aa,Forma f,double x,double y){ struct arena* a=(struct arena*)aa; a_gar(a); a->v[a->n].f=f; a->v[a->n].x=x; a->v[a->n].y=y; a->n++; }
int arenaCount(Arena aa){ struct arena* a=(struct arena*)aa; return a->n; }
Forma arenaGet(Arena aa,int i){ struct arena* a=(struct arena*)aa; return a->v[i].f; }
double arenaGetX(Arena aa,int i){ struct arena* a=(struct arena*)aa; return a->v[i].x; }
double arenaGetY(Arena aa,int i){ struct arena* a=(struct arena*)aa; return a->v[i].y; }
void arenaLimpa(Arena aa){ struct arena* a=(struct arena*)aa; a->n=0; }

typedef struct carnode { int id; Carreg c; struct carnode* n; } CarNode;
typedef struct dispnode { int id; Disp d; struct dispnode* n; } DispNode;

struct jogo { BancoGlobal bg; CarNode* car; DispNode* disps; Arena arena; int totIns; int totDsp; int totEsm; int totClo; };

Jogo criaJogo(BancoGlobal bg){ struct jogo* j=(struct jogo*)malloc(sizeof(struct jogo)); j->bg=bg; j->car=NULL; j->disps=NULL; j->arena=criaArena(); j->totIns=0; j->totDsp=0; j->totEsm=0; j->totClo=0; return (Jogo)j; }
void destroiJogo(Jogo jj){ struct jogo* j=(struct jogo*)jj; while(j->car){ CarNode* x=j->car; j->car=x->n; destroiCarreg(x->c); free(x); } while(j->disps){ DispNode* y=j->disps; j->disps=y->n; destroiDisp(y->d); free(y); } destroiArena(j->arena); free(j); }
static CarNode* buscaC(struct jogo* j,int id){ CarNode* p=j->car; while(p){ if(p->id==id) return p; p=p->n; } return NULL; }
static DispNode* buscaD(struct jogo* j,int id){ DispNode* p=j->disps; while(p){ if(p->id==id) return p; p=p->n; } return NULL; }
Carreg jogoGetCarreg(Jogo jj,int id,int cria){ struct jogo* j=(struct jogo*)jj; CarNode* p=buscaC(j,id); if(p) return p->c; if(!cria) return NULL; CarNode* x=(CarNode*)malloc(sizeof(CarNode)); x->id=id; x->c=criaCarreg(id); x->n=j->car; j->car=x; return x->c; }
Disp jogoGetDisp(Jogo jj,int id,int cria){ struct jogo* j=(struct jogo*)jj; DispNode* p=buscaD(j,id); if(p) return p->d; if(!cria) return NULL; DispNode* y=(DispNode*)malloc(sizeof(DispNode)); y->id=id; y->d=criaDisp(id); y->n=j->disps; j->disps=y; return y->d; }
void jogoCarregaDoChao(Jogo jj,int cid,int n){ struct jogo* j=(struct jogo*)jj; Carreg c=jogoGetCarreg(j,cid,1); int k=n; int qtd=bancoQuantidade(getChao(j->bg)); if(k>qtd) k=qtd; for(int i=0;i<k;i++){ Forma f=formaDup(bancoGet(getChao(j->bg),i)); } if(k>0) for(int i=0;i<k;i++){ Forma f=formaDup(bancoGet(getChao(j->bg),i)); carregPush(c,f); } bancoRemovePrimeiros(getChao(j->bg),k); }
void jogoEmpilhaChao(Jogo jj,Forma f){ struct jogo* j=(struct jogo*)jj; bancoInsereNoChao(getChao(j->bg),f); }
int jogoChaoQtd(Jogo jj){ struct jogo* j=(struct jogo*)jj; return bancoQuantidade(getChao(j->bg)); }
void jogoArenaDispara(Jogo jj,Disp d,double dx,double dy,char modo){ struct jogo* j=(struct jogo*)jj; double x=0,y=0; Forma f=dispFire(d,dx,dy,modo,&x,&y); if(f){ formaSetPos(f,x,y); arenaLanca(j->arena,f,x,y); j->totDsp++; } }

static int inter(Forma a,Forma b)
{
    int ta=formaTipo(a), tb=formaTipo(b);
    if(ta==2 && tb==2) return interRectRect(formaX(a),formaY(a),formaW(a),formaH(a),formaX(b),formaY(b),formaW(b),formaH(b));
    if(ta==1 && tb==1) return interCircCirc(formaX(a),formaY(a),formaR(a),formaX(b),formaY(b),formaR(b));
    if(ta==2 && tb==1) return interRectCirc(formaX(a),formaY(a),formaW(a),formaH(a),formaX(b),formaY(b),formaR(b));
    if(ta==1 && tb==2) return interRectCirc(formaX(b),formaY(b),formaW(b),formaH(b),formaX(a),formaY(a),formaR(a));
    if(ta==3 && tb==2) return interRectSeg(formaX(b),formaY(b),formaW(b),formaH(b),formaX(a),formaY(a),formaX2(a),formaY2(a));
    if(ta==2 && tb==3) return interRectSeg(formaX(a),formaY(a),formaW(a),formaH(a),formaX(b),formaY(b),formaX2(b),formaY2(b));
    if(ta==3 && tb==1){ double d=distPontoSeg(formaX(b),formaY(b),formaX(a),formaY(a),formaX2(a),formaY2(a)); return d<=formaR(b); }
    if(ta==1 && tb==3){ double d=distPontoSeg(formaX(a),formaY(a),formaX(b),formaY(b),formaX2(b),formaY2(b)); return d<=formaR(a); }
    if(ta==3 && tb==3) return interSegSeg(formaX(a),formaY(a),formaX2(a),formaY2(a),formaX(b),formaY(b),formaX2(b),formaY2(b));
    if(ta==4){ int n=util_strlen(formaTxt(a)); double cl=10.0*n; double xa=formaX(a), ya=formaY(a); double x1=xa, y1=ya, x2=xa+cl, y2=ya; if(formaAnc(a)=='f'){ x1=xa-cl; y1=ya; x2=xa; y2=ya; } else if(formaAnc(a)=='m'){ x1=xa-cl/2.0; y1=ya; x2=xa+cl/2.0; y2=ya; } Forma fa=a, fb=b; int tb2=formaTipo(b); if(tb2==2) return interRectSeg(formaX(b),formaY(b),formaW(b),formaH(b),x1,y1,x2,y2); if(tb2==1){ double d=distPontoSeg(formaX(b),formaY(b),x1,y1,x2,y2); return d<=formaR(b); } if(tb2==3) return interSegSeg(x1,y1,x2,y2,formaX(b),formaY(b),formaX2(b),formaY2(b)); if(tb2==4){ int m=util_strlen(formaTxt(b)); double cl2=10.0*m; double xb=formaX(b), yb=formaY(b), u1=xb, v1=yb, u2=xb+cl2, v2=yb; if(formaAnc(b)=='f'){ u1=xb-cl2; v1=yb; u2=xb; v2=yb; } else if(formaAnc(b)=='m'){ u1=xb-cl2/2.0; v1=yb; u2=xb+cl2/2.0; v2=yb; } return interSegSeg(x1,y1,x2,y2,u1,v1,u2,v2); } return 0; }
    if(tb==4) return inter(b,a);
    return 0;
}

static void corBDe(Forma dst,Forma src){ const char* c=formaCorP(src); if(c&&c[0]) formaSetCorB(dst,c); }
static int maxIdBanco(Banco b){ int n=bancoQuantidade(b); int mx=0; for(int i=0;i<n;i++){ int id=formaId(bancoGet(b,i)); if(id>mx) mx=id; } return mx; }

double jogoCalc(Jogo jj,double** ax,double** ay,int* nsm,double* pont,int* totIns,int* totDsp,int* totEsm,int* totClo)
{
    struct jogo* j=(struct jogo*)jj;
    int n=arenaCount(j->arena);
    int cap=64; double* vx=(double*)malloc(cap*sizeof(double)); double* vy=(double*)malloc(cap*sizeof(double)); int ns=0;
    double score=0.0; int clones=0; int esm=0;
    for(int i=0;i<n-1;i+=2)
    {
        Forma I=arenaGet(j->arena,i);
        Forma J=arenaGet(j->arena,i+1);
        double xi=arenaGetX(j->arena,i), yi=arenaGetY(j->arena,i);
        int ov=inter(I,J);
        if(ov)
        {
            double ai=formaArea(I), aj=formaArea(J);
            if(ai<aj)
            {
                if(ns>=cap){ cap*=2; double* nx=(double*)realloc(vx,cap*sizeof(double)); double* ny=(double*)realloc(vy,cap*sizeof(double)); vx=nx; vy=ny; }
                vx[ns]=xi; vy[ns]=yi; ns++;
                score+=ai; esm++;
                jogoEmpilhaChao(j,formaDup(J));
            }
            else
            {
                corBDe(J,I);
                jogoEmpilhaChao(j,formaDup(I));
                jogoEmpilhaChao(j,formaDup(J));
                Forma C=formaClona(I,1);
                int nid=maxIdBanco(getChao(j->bg))+1;
                ((int*)((char*)C))[1]=nid;
                clones++;
                jogoEmpilhaChao(j,C);
            }
        }
        else
        {
            jogoEmpilhaChao(j,formaDup(I));
            jogoEmpilhaChao(j,formaDup(J));
        }
    }
    arenaLimpa(j->arena);
    *ax=vx; *ay=vy; *nsm=ns; *pont=score; *totIns=&j->totIns?j->totIns:0; *totDsp=j->totDsp; *totEsm=esm; *totClo=clones;
    return score;
}

Banco jogoGetChao(Jogo jj){ struct jogo* j=(struct jogo*)jj; return getChao(j->bg); }
