#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pilha.h"
#include "fila.h"
#include "formas.h"
#include "disparador.h"
int main(int argc, char** argv){
    const char* bed = NULL;
    const char* arqgeo = NULL;
    const char* bsd = NULL;
    const char* arqqry = NULL;
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],"-e")==0 && i+1<argc){ bed = argv[++i]; continue; }
        if(strcmp(argv[i],"-f")==0 && i+1<argc){ arqgeo = argv[++i]; continue; }
        if(strcmp(argv[i],"-o")==0 && i+1<argc){ bsd = argv[++i]; continue; }
        if(strcmp(argv[i],"-q")==0 && i+1<argc){ arqqry = argv[++i]; continue; }
    }
    (void)bed;
    (void)arqgeo;
    (void)bsd;
    (void)arqqry;
    return 0;
}
