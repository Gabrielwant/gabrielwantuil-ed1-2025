#include <stdlib.h>
#include "fila.h"
struct fila {
    int capacidade;
    int ini;
    int fim;
    int n;
    void** dados;
};
Fila* criaFila(){
    Fila* f = malloc(sizeof(Fila));
    if(!f) return NULL;
    f->capacidade = 16;
    f->ini = 0;
    f->fim = 0;
    f->n = 0;
    f->dados = malloc(sizeof(void*) * f->capacidade);
    if(!f->dados){ free(f); return NULL; }
    return f;
}
void liberaFila(Fila* f){
    if(!f) return;
    free(f->dados);
    free(f);
}
int filaVazia(Fila* f){
    if(!f) return 1;
    return f->n == 0;
}
int filaEnqueue(Fila* f, void* elem){
    if(!f) return 0;
    if(f->n >= f->capacidade){
        int nc = f->capacidade * 2;
        void** nd = malloc(sizeof(void*) * nc);
        if(!nd) return 0;
        for(int i=0;i<f->n;i++) nd[i] = f->dados[(f->ini + i) % f->capacidade];
        free(f->dados);
        f->dados = nd;
        f->capacidade = nc;
        f->ini = 0;
        f->fim = f->n;
    }
    f->dados[f->fim++] = elem;
    if(f->fim >= f->capacidade) f->fim = 0;
    f->n++;
    return 1;
}
void* filaDequeue(Fila* f){
    if(!f || f->n == 0) return NULL;
    void* r = f->dados[f->ini++];
    if(f->ini >= f->capacidade) f->ini = 0;
    f->n--;
    return r;
}
void* filaPrimeiro(Fila* f){
    if(!f || f->n == 0) return NULL;
    return f->dados[f->ini];
}
