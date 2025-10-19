
#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "util.h"

struct args_ { char entrada[512]; char geo[256]; char qry[256]; char saida[512]; int temQry; };
typedef struct args_ A;
Args criaArgs(void){ A* a=(A*)malloc(sizeof(A)); if(!a) return NULL; a->entrada[0]=0;a->geo[0]=0;a->qry[0]=0;a->saida[0]=0;a->temQry=0; return (Args)a; }
void destroiArgs(Args aa){ A* a=(A*)aa; if(a) free(a); }
static int igual(const char* s,const char* t){ return util_strcmp(s,t)==0; }
int parseArgs(Args aa,int argc,char** argv){ A* a=(A*)aa; int i=1; while(i<argc){ if(igual(argv[i],"-e")){ i++; if(i>=argc) return 0; util_copy(a->entrada,argv[i],511); } else if(igual(argv[i],"-f")){ i++; if(i>=argc) return 0; util_copy(a->geo,argv[i],255); } else if(igual(argv[i],"-q")){ i++; if(i>=argc) return 0; util_copy(a->qry,argv[i],255); a->temQry=1; } else if(igual(argv[i],"-o")){ i++; if(i>=argc) return 0; util_copy(a->saida,argv[i],511); } i++; } if(a->geo[0]==0||a->saida[0]==0) return 0; return 1; }
const char* getEntradaDir(Args aa){ return ((A*)aa)->entrada; }
const char* getGeo(Args aa){ return ((A*)aa)->geo; }
const char* getQry(Args aa){ return ((A*)aa)->temQry?((A*)aa)->qry:NULL; }
const char* getSaidaDir(Args aa){ return ((A*)aa)->saida; }
