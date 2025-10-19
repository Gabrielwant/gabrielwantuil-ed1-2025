
#include <stdio.h>
#include <stdlib.h>
#include "parser_qry.h"
#include "util.h"
#include "jogo.h"
#include "svg.h"
#include "saida.h"
#include "banco.h"

static int tok(FILE* f,char* b,int m){ int c=0,i=0,l=0; while((c=fgetc(f))!=EOF){ if(c==' '||c=='\t'||c=='\r'||c=='\n'){ if(l) break; else continue; } b[i++]=(char)c; l=1; if(i>=m-1) break; } b[i]=0; return i>0; }
static double Ld(FILE* f){ char b[64]; if(!tok(f,b,64)) return 0.0; return util_atof(b); }
static int Li(FILE* f){ char b[32]; if(!tok(f,b,32)) return 0; return util_atoi(b); }
static void Ls(FILE* f,char* d,int m){ char b[64]; if(!tok(f,b,64)){ d[0]=0; return; } util_copy(d,b,m-1); }

int processaQry(const char* dir,const char* nome,BancoGlobal bg,const char* saidaDir,const char* baseGeo)
{
    char cam[1024]; if(dir && util_strlen(dir)>0){ util_copy(cam,dir,1023); int n=util_strlen(cam); if(cam[n-1]!='/'){ cam[n]='/'; cam[n+1]=0; } util_join3(cam,cam,nome,"",1023); } else util_copy(cam,nome,1023);
    FILE* f=fopen(cam,"r"); if(!f) return 0;
    Jogo j=criaJogo(bg);
    char tokc[32];
    while(tok(f,tokc,32))
    {
        if(util_strcmp(tokc,"pd")==0)
        {
            int id=Li(f); double x=Ld(f), y=Ld(f);
            Disp d=jogoGetDisp(j,id,1); dispPos(d,x,y);
        }
        else if(util_strcmp(tokc,"lc")==0)
        {
            int cid=Li(f); int n=Li(f);
            jogoCarregaDoChao(j,cid,n);
        }
        else if(util_strcmp(tokc,"atch")==0)
        {
            int d=Li(f); int ce=Li(f); int cd=Li(f);
            Disp dp=jogoGetDisp(j,d,1);
            Carreg e=jogoGetCarreg(j,ce,1);
            Carreg dr=jogoGetCarreg(j,cd,1);
            dispLiga(dp,e,dr);
        }
        else if(util_strcmp(tokc,"shft")==0)
        {
            int d=Li(f); char lado[8]; Ls(f,lado,8); int n=Li(f);
            Disp dp=jogoGetDisp(j,d,1);
            for(int i=0;i<n;i++){ dispShift(dp,lado[0]); }
        }
        else if(util_strcmp(tokc,"dsp")==0)
        {
            int d=Li(f); double dx=Ld(f), dy=Ld(f); char modo[8]; Ls(f,modo,8);
            Disp dp=jogoGetDisp(j,d,1);
            jogoArenaDispara(j,dp,dx,dy,modo[0]);
        }
        else if(util_strcmp(tokc,"rjd")==0)
        {
            int d=Li(f); char lado[8]; Ls(f,lado,8); double dx=Ld(f), dy=Ld(f), ix=Ld(f), iy=Ld(f);
            Disp dp=jogoGetDisp(j,d,1);
            int passo=0;
            while(1)
            {
                Forma cur=dispShift(dp,lado[0]);
                if(!cur) break;
                jogoArenaDispara(j,dp,dx+passo*ix,dy+passo*iy,'i');
                passo++;
            }
        }
        else if(util_strcmp(tokc,"calc")==0)
        {
            double *ax=NULL,*ay=NULL; int nsm=0; double pont=0; int ti=0, td=0, te=0, tc=0;
            jogoCalc(j,&ax,&ay,&nsm,&pont,&ti,&td,&te,&tc);
            escreveSvgQryFinal(saidaDir,baseGeo,nome,jogoGetChao(j),ax,ay,nsm);
            escreveTxtFinal(saidaDir,baseGeo,nome,pont,ti,td,te,tc);
            if(ax) free(ax); if(ay) free(ay);
        }
        else
        {
            int c=0; while((c=fgetc(f))!=EOF && c!='\n'){}
        }
    }
    fclose(f);
    destroiJogo(j);
    return 1;
}
