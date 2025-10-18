#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "formas.h"
#include "disparador.h"

void processaQry(const char *caminhoGeo, const char *caminhoQry, const char *saidaDir)
{
  FILE *geo = fopen(caminhoGeo, "r");
  if (!geo)
  {
    printf("Erro ao abrir %s\n", caminhoGeo);
    return;
  }

  FILE *qry = fopen(caminhoQry, "r");
  if (!qry)
  {
    printf("Erro ao abrir %s\n", caminhoQry);
    fclose(geo);
    return;
  }

  char saidaPath[256];
  sprintf(saidaPath, "%s/saida-final.svg", saidaDir);

  FILE *svg = fopen(saidaPath, "w");
  if (!svg)
  {
    printf("Erro ao criar %s\n", saidaPath);
    fclose(geo);
    fclose(qry);
    return;
  }

  fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
  printf("\n=== Executando GEO (%s) e QRY (%s) ===\n", caminhoGeo, caminhoQry);

  char tipo[5];
  int id;
  double x, y, w, h, r;
  char corb[30], corp[30];
  char fontFamily[30] = "sans";
  char fontWeight[10] = "n";
  double fontSize = 12;

  // --- FORMAS DO GEO ---
  while (fscanf(geo, "%s", tipo) == 1)
  {
    if (strcmp(tipo, "c") == 0)
    {
      fscanf(geo, "%d %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp);
      fprintf(svg, "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" fill=\"%s\" stroke=\"%s\" />\n",
              x, y, r, corp, corb);
    }
    else if (strcmp(tipo, "r") == 0)
    {
      fscanf(geo, "%d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp);
      fprintf(svg, "<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" fill=\"%s\" stroke=\"%s\" />\n",
              x, y, w, h, corp, corb);
    }
    else if (strcmp(tipo, "l") == 0)
    {
      double x1, y1, x2, y2;
      char cor[30];
      fscanf(geo, "%d %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, cor);
      fprintf(svg, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\" />\n",
              x1, y1, x2, y2, cor);
    }
    else if (strcmp(tipo, "ts") == 0)
    {
      fscanf(geo, "%s %s %lf", fontFamily, fontWeight, &fontSize);
      printf("Fonte alterada: %s %s %.1f\n", fontFamily, fontWeight, fontSize);
    }
    else if (strcmp(tipo, "t") == 0)
    {
      char ancora, texto[256];
      fscanf(geo, "%d %lf %lf %s %s %c", &id, &x, &y, corb, corp, &ancora);
      fgets(texto, sizeof(texto), geo);
      texto[strcspn(texto, "\n")] = 0;
      printf("Lendo texto %d: '%s'\n", id, texto);
      fprintf(svg,
              "<text x=\"%.2f\" y=\"%.2f\" fill=\"%s\" stroke=\"%s\" font-family=\"%s\" font-weight=\"%s\" font-size=\"%.1f\" text-anchor=\"%c\">%s</text>\n",
              x, y, corp, corb, fontFamily, fontWeight, fontSize, ancora, texto);
    }
  }

  fclose(geo);

  // --- EXECUTA QRY ---
  char comando[20];
  Disparador *d = NULL;
  double pontuacaoTotal = 0;

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
      {
        dspDisparador(d, dx, dy, modo);
        fprintf(svg, "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"10\" fill=\"red\" stroke=\"black\" />\n",
                getXDisparador(d), getYDisparador(d));
        pontuacaoTotal += 314.16;
      }
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
  }

  fprintf(svg, "<text x=\"20\" y=\"40\" fill=\"black\">Pontuação total: %.2f</text>\n", pontuacaoTotal);
  fprintf(svg, "</svg>\n");
  fclose(qry);
  fclose(svg);

  printf("\nArquivo SVG final gerado em: %s\n", saidaPath);
}
