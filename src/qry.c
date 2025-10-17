#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry.h"
#include "disparador.h"

void processaQry(const char *caminhoQry)
{
  FILE *qry = fopen(caminhoQry, "r");
  if (!qry)
  {
    printf("Erro ao abrir %s\n", caminhoQry);
    return;
  }

  printf("\n=== Executando arquivo QRY: %s ===\n", caminhoQry);

  char comando[20];

  while (fscanf(qry, "%s", comando) == 1)
  {
    if (strcmp(comando, "pd") == 0)
    {
      int id;
      double x, y;
      fscanf(qry, "%d %lf %lf", &id, &x, &y);
      printf("[pd] Criando disparador %d em (%.2f, %.2f)\n", id, x, y);
      Disparador *d = criaDisparador(id, x, y);
      liberaDisparador(d);
    }

    else if (strcmp(comando, "lc") == 0)
    {
      int id;
      double x, y;
      fscanf(qry, "%d %lf %lf", &id, &x, &y);
      printf("[lc] Criando carregador %d em (%.2f, %.2f)\n", id, x, y);
    }

    else if (strcmp(comando, "atch") == 0)
    {
      int id, esq, dir;
      fscanf(qry, "%d %d %d", &id, &esq, &dir);
      printf("[atch] Ligando disparador %d aos carregadores %d e %d\n", id, esq, dir);
    }

    else if (strcmp(comando, "shft") == 0)
    {
      int id, n;
      char lado;
      fscanf(qry, "%d %c %d", &id, &lado, &n);
      printf("[shft] Movendo disparador %d para %c %d vezes\n", id, lado, n);
    }

    else if (strcmp(comando, "dsp") == 0)
    {
      int id;
      double dx, dy;
      char modo;
      fscanf(qry, "%d %lf %lf %c", &id, &dx, &dy, &modo);
      printf("[dsp] Disparando com disparador %d deslocamento (%.2f, %.2f) modo %c\n", id, dx, dy, modo);
    }

    else if (strcmp(comando, "rjd") == 0)
    {
      int id;
      fscanf(qry, "%d", &id);
      printf("[rjd] Removendo disparador %d\n", id);
    }

    else if (strcmp(comando, "calc") == 0)
    {
      printf("[calc] Calculando e gerando SVG final...\n");
    }

    else
    {
      printf("[?] Comando desconhecido: %s\n", comando);
    }
  }

  fclose(qry);
}
