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

  FILE *svg = fopen("saida/saida-final.svg", "w");
  if (!svg)
  {
    printf("Erro ao criar saida/saida-final.svg\n");
    fclose(qry);
    return;
  }

  fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");

  printf("\n=== Executando arquivo QRY: %s ===\n", caminhoQry);

  char comando[20];
  Disparador *d = NULL;

  while (fscanf(qry, "%s", comando) == 1)
  {
    if (strcmp(comando, "pd") == 0)
    {
      int id;
      double x, y;
      fscanf(qry, "%d %lf %lf", &id, &x, &y);
      printf("[pd] Criando disparador %d em (%.2f, %.2f)\n", id, x, y);
      d = criaDisparador(id, x, y);
      fprintf(svg, "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"10\" fill=\"blue\" stroke=\"black\" />\n", x, y);
    }

    else if (strcmp(comando, "lc") == 0)
    {
      int id;
      double x, y;
      fscanf(qry, "%d %lf %lf", &id, &x, &y);
      printf("[lc] Criando carregador %d em (%.2f, %.2f)\n", id, x, y);
      fprintf(svg, "<rect x=\"%.2f\" y=\"%.2f\" width=\"20\" height=\"20\" fill=\"yellow\" stroke=\"black\" />\n", x, y);
    }

    else if (strcmp(comando, "atch") == 0)
    {
      int id, esq, dir;
      fscanf(qry, "%d %d %d", &id, &esq, &dir);
      printf("[atch] Ligando disparador %d aos carregadores %d e %d\n", id, esq, dir);
      if (d)
        atchDisparador(d, esq, dir);
    }

    else if (strcmp(comando, "shft") == 0)
    {
      int id, n;
      char lado;
      fscanf(qry, "%d %c %d", &id, &lado, &n);
      printf("[shft] Movendo disparador %d para %c %d vezes\n", id, lado, n);
      if (d)
        shftDisparador(d, lado, n);
      fprintf(svg, "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"10\" fill=\"green\" stroke=\"black\" />\n",
              getXDisparador(d), getYDisparador(d));
    }

    else if (strcmp(comando, "dsp") == 0)
    {
      int id;
      double dx, dy;
      char modo;
      fscanf(qry, "%d %lf %lf %c", &id, &dx, &dy, &modo);
      printf("[dsp] Disparando com disparador %d deslocamento (%.2f, %.2f) modo %c\n", id, dx, dy, modo);
      if (d)
        dspDisparador(d, dx, dy, modo);
      fprintf(svg, "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"10\" fill=\"red\" stroke=\"black\" />\n",
              getXDisparador(d), getYDisparador(d));
    }

    else if (strcmp(comando, "rjd") == 0)
    {
      int id;
      fscanf(qry, "%d", &id);
      printf("[rjd] Removendo disparador %d\n", id);
      if (d)
      {
        fprintf(svg, "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"10\" fill=\"gray\" stroke=\"black\" />\n",
                getXDisparador(d), getYDisparador(d));
        liberaDisparador(d);
        d = NULL;
      }
    }

    else if (strcmp(comando, "calc") == 0)
    {
      printf("[calc] Calculando e gerando SVG final...\n");
      fprintf(svg, "<text x=\"10\" y=\"20\" fill=\"black\">Simulação concluída.</text>\n");
    }

    else
    {
      printf("[?] Comando desconhecido: %s\n", comando);
    }
  }

  fprintf(svg, "</svg>\n");
  fclose(qry);
  fclose(svg);
  printf("SVG final gerado em: saida/saida-final.svg\n");
}
