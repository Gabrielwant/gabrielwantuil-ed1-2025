#include <stdio.h>
#include "pilha.h"

int main()
{
  Pilha *p = criaPilha();
  int a = 10, b = 20, c = 30;

  pilhaPush(p, &a);
  pilhaPush(p, &b);
  pilhaPush(p, &c);

  printf("Tamanho: %d\n", tamanhoPilha(p));
  printf("Topo: %d\n", *(int *)pilhaTopo(p));

  printf("Pop: %d\n", *(int *)pilhaPop(p));
  printf("Novo topo: %d\n", *(int *)pilhaTopo(p));
  printf("Tamanho final: %d\n", tamanhoPilha(p));

  liberaPilha(p);
  return 0;
}
