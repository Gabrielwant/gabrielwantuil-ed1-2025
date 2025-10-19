
#include <stdio.h>
#include <stdlib.h>
#include "banco.h"
#include "formas.h"
#include "util.h"

struct bancoGlobal { Banco chao; char fam[32]; char peso[8]; double tam; };
BancoGlobal criaBancoGlobal(void){ struct bancoGlobal* bg=(struct bancoGlobal*)malloc(sizeof(struct bancoGlobal)); bg->chao=criaBanco(); util_copy(bg->fam,"sans",31); util_copy(bg->peso,"n",7); bg->tam=12.0; return bg; }
void destroiBancoGlobal(BancoGlobal bg){ struct bancoGlobal* g=(struct bancoGlobal*)bg; destroiBanco(g->chao); free(g); }
Banco getChao(BancoGlobal bg){ return ((struct bancoGlobal*)bg)->chao; }
void setEstiloTexto(BancoGlobal bg,const char* fam,const char* peso,double tam){ struct bancoGlobal* g=(struct bancoGlobal*)bg; util_copy(g->fam,fam,31); util_copy(g->peso,peso,7); g->tam=tam; }
void getEstiloTexto(BancoGlobal bg,char* fam,char* peso,double* tam){ struct bancoGlobal* g=(struct bancoGlobal*)bg; util_copy(fam,g->fam,31); util_copy(peso,g->peso,7); *tam=g->tam; }
int bancoMaxId(BancoGlobal bg){ struct bancoGlobal* g=(struct bancoGlobal*)bg; int n=bancoQuantidade(g->chao); int mx=0; for(int i=0;i<n;i++){ int id=formaId(bancoGet(g->chao,i)); if(id>mx) mx=id; } return mx; }
void bancoFixMaxId(BancoGlobal bg,int id){}
