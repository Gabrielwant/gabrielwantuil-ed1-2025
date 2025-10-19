
#include <stdio.h>
#include <stdlib.h>
#include "parser_geo.h"
#include "util.h"
#include "banco.h"
#include "formas.h"

static int tok(FILE* f,char* b,int m){ int c=0,i=0,l=0; while((c=fgetc(f))!=EOF){ if(c==' '||c=='\t'||c=='\r'||c=='\n'){ if(l) break; else continue; } b[i++]=(char)c; l=1; if(i>=m-1) break; } b[i]=0; return i>0; }
static double Ld(FILE* f){ char b[64]; if(!tok(f,b,64)) return 0.0; return util_atof(b); }
static int Li(FILE* f){ char b[32]; if(!tok(f,b,32)) return 0; return util_atoi(b); }
static void Ls(FILE* f,char* d,int m){ char b[64]; if(!tok(f,b,64)){ d[0]=0; return; } util_copy(d,b,m-1); }

int processaGeo(const char* dir,const char* nome,BancoGlobal bg)
{
    char cam[1024]; if(dir && util_strlen(dir)>0){ util_copy(cam,dir,1023); int n=util_strlen(cam); if(cam[n-1]!='/'){ cam[n]='/'; cam[n+1]=0; } util_join3(cam,cam,nome,"",1023); } else util_copy(cam,nome,1023);
    FILE* f=fopen(cam,"r"); if(!f) return 0;
    char t[32];
    while(tok(f,t,32))
    {
        if(util_strcmp(t,"c")==0)
        {
            int id=Li(f); double x=Ld(f), y=Ld(f), r=Ld(f); char cb[32], cp[32]; Ls(f,cb,32); Ls(f,cp,32);
            bancoInsereCirculo(getChao(bg),id,x,y,r,cb,cp);
        }
        else if(util_strcmp(t,"r")==0)
        {
            int id=Li(f); double x=Ld(f), y=Ld(f), w=Ld(f), h=Ld(f); char cb[32], cp[32]; Ls(f,cb,32); Ls(f,cp,32);
            bancoInsereRetangulo(getChao(bg),id,x,y,w,h,cb,cp);
        }
        else if(util_strcmp(t,"l")==0)
        {
            int id=Li(f); double x1=Ld(f), y1=Ld(f), x2=Ld(f), y2=Ld(f); char ccor[32]; Ls(f,ccor,32);
            bancoInsereLinha(getChao(bg),id,x1,y1,x2,y2,ccor);
        }
        else if(util_strcmp(t,"t")==0)
        {
            int id=Li(f); double x=Ld(f), y=Ld(f); char cb[32], cp[32]; char anc[8]; Ls(f,cb,32); Ls(f,cp,32); Ls(f,anc,8);
            char rest[256]; int c=0,i=0; while((c=fgetc(f))!=EOF && c!='\n'){ if(i<255) rest[i++]=(char)c; } rest[i]=0;
            bancoInsereTexto(getChao(bg),id,x,y,anc[0],cb,cp,rest);
        }
        else if(util_strcmp(t,"ts")==0)
        {
            char fam[32], peso[8], tmp[32]; Ls(f,fam,32); Ls(f,peso,8); Ls(f,tmp,32);
            double tam=util_atof(tmp); setEstiloTexto(bg,fam,peso,tam);
        }
        else
        {
            int c=0; while((c=fgetc(f))!=EOF && c!='\n'){}
        }
    }
    fclose(f);
    return 1;
}
