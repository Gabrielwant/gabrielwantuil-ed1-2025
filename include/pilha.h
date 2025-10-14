#ifndef PILHA_H
#define PILHA_H
typedef struct pilha Pilha;
Pilha* criaPilha();
void liberaPilha(Pilha* p);
int pilhaVazia(Pilha* p);
int pilhaPush(Pilha* p, void* elem);
void* pilhaPop(Pilha* p);
void* pilhaTopo(Pilha* p);
#endif
