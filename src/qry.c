#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry.h"

void processaQry(const char *caminhoQry)
{
  FILE *qry = fopen(caminhoQry, "r");
  if (!qry)
  {
    printf("Erro ao abrir %s\n", caminhoQry);
    return;
  }

  printf("Lendo arquivo QRY: %s\n", caminhoQry);

  char comando[10];
  while (fscanf(qry, "%s", comando) == 1)
  {
    printf("Comando encontrado: %s\n", comando);
    // Aqui no Dia 7, a gente vai começar a tratar cada comando
  }

  fclose(qry);
}
