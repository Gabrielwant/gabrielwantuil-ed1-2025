
#include <stdio.h>
#include <stdlib.h>
#include "saida.h"
#include "util.h"

void escreveTxtFinal(const char* saidaDir,const char* baseGeo,const char* baseQry,double pont,int totIns,int totDsp,int totEsm,int totClo)
{
    char base[800]; base[0]=0; int n=util_strlen(baseGeo);
    int i=n-1; while(i>=0 && baseGeo[i]!='/') i--;
    const char* geo=(i>=0)?baseGeo+i+1:baseGeo;
    char outname[1024]; util_copy(outname,saidaDir,1023);
    int k=util_strlen(outname);
    if(k>0 && outname[k-1]!='/'){ outname[k]='/'; outname[k+1]=0; }
    char mid[1024]; util_copy(mid,geo,1023);
    int m=util_strlen(mid);
    while(m>0 && mid[m-1]!='.') m--;
    mid[m-1]=0;
    char fin[1400];
    util_join3(fin,outname,mid,"-",1399);
    util_join3(fin,fin,baseQry,".txt",1399);
    FILE* f=fopen(fin,"w");
    if(!f) return;
    fprintf(f,"Pontuacao final: %.2f\n",pont);
    fprintf(f,"Instrucoes: %d\n",totIns);
    fprintf(f,"Disparos: %d\n",totDsp);
    fprintf(f,"Esmagadas: %d\n",totEsm);
    fprintf(f,"Clonadas: %d\n",totClo);
    fclose(f);
}
