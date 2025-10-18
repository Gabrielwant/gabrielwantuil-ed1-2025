#include <stdio.h>
#include <stdlib.h>
#include "arena.h"

struct nodo
{
  Forma *f;
  int destruida;
  struct nodo *prox;
};

struct arena
{
  struct nodo *ini;
  double pontuacao;
};

Arena *criaArena(void)
{
  Arena *a = malloc(sizeof(Arena));
  a->ini = NULL;
  a->pontuacao = 0;
  return a;
}

void adicionaFormaArena(Arena *a, Forma *f)
{
  struct nodo *n = malloc(sizeof(struct nodo));
  n->f = f;
  n->destruida = 0;
  n->prox = NULL;
  if (!a->ini)
    a->ini = n;
  else
  {
    struct nodo *p = a->ini;
    while (p->prox)
      p = p->prox;
    p->prox = n;
  }
}

void processaSobreposicoes(Arena *a)
{
  struct nodo *i = a->ini;
  while (i && i->prox)
  {
    struct nodo *j = i->prox;
    if (sobrepoe(i->f, j->f))
    {
      double ai = areaForma(i->f);
      double aj = areaForma(j->f);

      if (ai < aj)
      {
        a->pontuacao += ai;
        i->destruida = 1;
      }
      else
      {
        mudaCorBorda(j->f, getCorPreenchimento(i->f));
        a->pontuacao += aj;
        Forma *clone = clonaForma(i->f);
        trocaCores(clone);
        adicionaFormaArena(a, clone);
      }
    }
    i = i->prox;
  }
}

void escreveArenaSVG(Arena *a, FILE *svg)
{
  struct nodo *p = a->ini;
  while (p)
  {
    if (!p->destruida)
      desenhaForma(svg, p->f);
    p = p->prox;
  }
  fprintf(svg, "<text x=\"10\" y=\"20\" fill=\"black\">Pontuação total: %.2f</text>\n", a->pontuacao);
}

double getPontuacao(Arena *a)
{
  return a->pontuacao;
}

void liberaArena(Arena *a)
{
  struct nodo *p = a->ini;
  while (p)
  {
    struct nodo *tmp = p->prox;
    liberaForma(p->f);
    free(p);
    p = tmp;
  }
  free(a);
}
