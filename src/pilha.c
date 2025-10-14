#include <stdlib.h>
#include "pilha.h"
struct pilha {
    int tamanho;
    int topo;
    void** dados;
};
Pilha* criaPilha(){
    Pilha* p = malloc(sizeof(Pilha));
    if(!p) return NULL;
    p->tamanho = 16;
    p->topo = 0;
    p->dados = malloc(sizeof(void*) * p->tamanho);
    if(!p->dados){ free(p); return NULL; }
    return p;
}
void liberaPilha(Pilha* p){
    if(!p) return;
    free(p->dados);
    free(p);
}
int pilhaVazia(Pilha* p){
    if(!p) return 1;
    return p->topo == 0;
}
int pilhaPush(Pilha* p, void* elem){
    if(!p) return 0;
    if(p->topo >= p->tamanho){
        int nt = p->tamanho * 2;
        void** nd = realloc(p->dados, sizeof(void*) * nt);
        if(!nd) return 0;
        p->dados = nd;
        p->tamanho = nt;
    }
    p->dados[p->topo++] = elem;
    return 1;
}
void* pilhaPop(Pilha* p){
    if(!p || p->topo == 0) return NULL;
    return p->dados[--p->topo];
}
void* pilhaTopo(Pilha* p){
    if(!p || p->topo == 0) return NULL;
    return p->dados[p->topo - 1];
}
