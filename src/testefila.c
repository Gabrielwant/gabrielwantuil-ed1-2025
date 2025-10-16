#include <stdio.h>
#include "fila.h"

int main()
{
  Fila *f = criaFila();
  int x = 1, y = 2, z = 3;

  insereFila(f, &x);
  insereFila(f, &y);
  insereFila(f, &z);

  printf("Tamanho: %d\n", tamanhoFila(f));
  printf("Frente: %d\n", *(int *)frenteFila(f));

  printf("Remove: %d\n", *(int *)removeFila(f));
  printf("Nova frente: %d\n", *(int *)frenteFila(f));
  printf("Tamanho final: %d\n", tamanhoFila(f));

  liberaFila(f);
  return 0;
}
