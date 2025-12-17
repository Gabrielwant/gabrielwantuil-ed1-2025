#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "forma.h"

#define PI 3.14159265358979323846

typedef struct circulo
{
  int id;
  double x, y, r;
  char corb[50];
  char corp[50];
} Circulo;

typedef struct retangulo
{
  int id;
  double x, y, w, h;
  char corb[50];
  char corp[50];
} Retangulo;

typedef struct linha
{
  int id;
  double x1, y1, x2, y2;
  char cor[50];
} Linha;

typedef struct texto
{
  int id;
  double x, y;
  char corb[50];
  char corp[50];
  char ancora;
  char texto[500];
} Texto;

typedef struct forma_str
{
  TipoForma tipo;
  void *dados;
} FormaStr;

Forma create_circulo(int id, double x, double y, double r, char *corb, char *corp)
{
  FormaStr *f = (FormaStr *)malloc(sizeof(FormaStr));
  Circulo *c = (Circulo *)malloc(sizeof(Circulo));

  c->id = id;
  c->x = x;
  c->y = y;
  c->r = r;
  strcpy(c->corb, corb);
  strcpy(c->corp, corp);

  f->tipo = CIRCULO;
  f->dados = c;
  return f;
}

Forma create_retangulo(int id, double x, double y, double w, double h, char *corb, char *corp)
{
  FormaStr *f = (FormaStr *)malloc(sizeof(FormaStr));
  Retangulo *r = (Retangulo *)malloc(sizeof(Retangulo));

  r->id = id;
  r->x = x;
  r->y = y;
  r->w = w;
  r->h = h;
  strcpy(r->corb, corb);
  strcpy(r->corp, corp);

  f->tipo = RETANGULO;
  f->dados = r;
  return f;
}

Forma create_linha(int id, double x1, double y1, double x2, double y2, char *cor)
{
  FormaStr *f = (FormaStr *)malloc(sizeof(FormaStr));
  Linha *l = (Linha *)malloc(sizeof(Linha));

  l->id = id;
  l->x1 = x1;
  l->y1 = y1;
  l->x2 = x2;
  l->y2 = y2;
  strcpy(l->cor, cor);

  f->tipo = LINHA;
  f->dados = l;
  return f;
}

Forma create_texto(int id, double x, double y, char *corb, char *corp, char ancora, char *texto)
{
  FormaStr *f = (FormaStr *)malloc(sizeof(FormaStr));
  Texto *t = (Texto *)malloc(sizeof(Texto));

  t->id = id;
  t->x = x;
  t->y = y;
  strcpy(t->corb, corb);
  strcpy(t->corp, corp);
  t->ancora = ancora;
  strcpy(t->texto, texto);

  f->tipo = TEXTO;
  f->dados = t;
  return f;
}

Forma clone_forma(Forma f, int novo_id)
{
  FormaStr *forma = (FormaStr *)f;

  switch (forma->tipo)
  {
  case CIRCULO:
  {
    Circulo *c = (Circulo *)forma->dados;
    return create_circulo(novo_id, c->x, c->y, c->r, c->corp, c->corb);
  }
  case RETANGULO:
  {
    Retangulo *r = (Retangulo *)forma->dados;
    return create_retangulo(novo_id, r->x, r->y, r->w, r->h, r->corp, r->corb);
  }
  case LINHA:
  {
    Linha *l = (Linha *)forma->dados;
    return create_linha(novo_id, l->x1, l->y1, l->x2, l->y2, l->cor);
  }
  case TEXTO:
  {
    Texto *t = (Texto *)forma->dados;
    return create_texto(novo_id, t->x, t->y, t->corp, t->corb, t->ancora, t->texto);
  }
  }
  return NULL;
}

TipoForma get_tipo_forma(Forma f)
{
  FormaStr *forma = (FormaStr *)f;
  return forma->tipo;
}

int get_id_forma(Forma f)
{
  FormaStr *forma = (FormaStr *)f;
  switch (forma->tipo)
  {
  case CIRCULO:
    return ((Circulo *)forma->dados)->id;
  case RETANGULO:
    return ((Retangulo *)forma->dados)->id;
  case LINHA:
    return ((Linha *)forma->dados)->id;
  case TEXTO:
    return ((Texto *)forma->dados)->id;
  }
  return -1;
}

double get_area_forma(Forma f)
{
  FormaStr *forma = (FormaStr *)f;

  switch (forma->tipo)
  {
  case CIRCULO:
  {
    Circulo *c = (Circulo *)forma->dados;
    return PI * c->r * c->r;
  }
  case RETANGULO:
  {
    Retangulo *r = (Retangulo *)forma->dados;
    return r->w * r->h;
  }
  case LINHA:
  {
    Linha *l = (Linha *)forma->dados;
    double dx = l->x2 - l->x1;
    double dy = l->y2 - l->y1;
    double comprimento = sqrt(dx * dx + dy * dy);
    return 2.0 * comprimento;
  }
  case TEXTO:
  {
    Texto *t = (Texto *)forma->dados;
    return 20.0 * strlen(t->texto);
  }
  }
  return 0.0;
}

void set_cor_borda_forma(Forma f, char *nova_cor)
{
  FormaStr *forma = (FormaStr *)f;

  switch (forma->tipo)
  {
  case CIRCULO:
  {
    Circulo *c = (Circulo *)forma->dados;
    strcpy(c->corb, nova_cor);
    break;
  }
  case RETANGULO:
  {
    Retangulo *r = (Retangulo *)forma->dados;
    strcpy(r->corb, nova_cor);
    break;
  }
  case TEXTO:
  {
    Texto *t = (Texto *)forma->dados;
    strcpy(t->corb, nova_cor);
    break;
  }
  case LINHA:
    break;
  }
}

char *get_cor_borda_forma(Forma f)
{
  FormaStr *forma = (FormaStr *)f;

  switch (forma->tipo)
  {
  case CIRCULO:
    return ((Circulo *)forma->dados)->corb;
  case RETANGULO:
    return ((Retangulo *)forma->dados)->corb;
  case TEXTO:
    return ((Texto *)forma->dados)->corb;
  case LINHA:
    return ((Linha *)forma->dados)->cor;
  }
  return NULL;
}

char *get_cor_preenchimento_forma(Forma f)
{
  FormaStr *forma = (FormaStr *)f;

  switch (forma->tipo)
  {
  case CIRCULO:
    return ((Circulo *)forma->dados)->corp;
  case RETANGULO:
    return ((Retangulo *)forma->dados)->corp;
  case TEXTO:
    return ((Texto *)forma->dados)->corp;
  case LINHA:
    return ((Linha *)forma->dados)->cor;
  }
  return NULL;
}

void move_forma(Forma f, double novo_x, double novo_y)
{
  FormaStr *forma = (FormaStr *)f;

  switch (forma->tipo)
  {
  case CIRCULO:
  {
    Circulo *c = (Circulo *)forma->dados;
    c->x = novo_x;
    c->y = novo_y;
    break;
  }
  case RETANGULO:
  {
    Retangulo *r = (Retangulo *)forma->dados;
    r->x = novo_x;
    r->y = novo_y;
    break;
  }
  case TEXTO:
  {
    Texto *t = (Texto *)forma->dados;
    t->x = novo_x;
    t->y = novo_y;
    break;
  }
  case LINHA:
    break;
  }
}

double get_x_forma(Forma f)
{
  FormaStr *forma = (FormaStr *)f;

  switch (forma->tipo)
  {
  case CIRCULO:
    return ((Circulo *)forma->dados)->x;
  case RETANGULO:
    return ((Retangulo *)forma->dados)->x;
  case TEXTO:
    return ((Texto *)forma->dados)->x;
  case LINHA:
    return ((Linha *)forma->dados)->x1;
  }
  return 0.0;
}

double get_y_forma(Forma f)
{
  FormaStr *forma = (FormaStr *)f;

  switch (forma->tipo)
  {
  case CIRCULO:
    return ((Circulo *)forma->dados)->y;
  case RETANGULO:
    return ((Retangulo *)forma->dados)->y;
  case TEXTO:
    return ((Texto *)forma->dados)->y;
  case LINHA:
    return ((Linha *)forma->dados)->y1;
  }
  return 0.0;
}

void escreve_forma_svg(Forma f, FILE *svg)
{
  FormaStr *forma = (FormaStr *)f;

  switch (forma->tipo)
  {
  case CIRCULO:
  {
    Circulo *c = (Circulo *)forma->dados;
    fprintf(svg, "  <circle cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" stroke=\"%s\" fill=\"%s\" />\n",
            c->x, c->y, c->r, c->corb, c->corp);
    break;
  }
  case RETANGULO:
  {
    Retangulo *r = (Retangulo *)forma->dados;
    fprintf(svg, "  <rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" stroke=\"%s\" fill=\"%s\" />\n",
            r->x, r->y, r->w, r->h, r->corb, r->corp);
    break;
  }
  case LINHA:
  {
    Linha *l = (Linha *)forma->dados;
    fprintf(svg, "  <line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\" />\n",
            l->x1, l->y1, l->x2, l->y2, l->cor);
    break;
  }
  case TEXTO:
  {
    Texto *t = (Texto *)forma->dados;
    char anchor[20];
    if (t->ancora == 'i')
      strcpy(anchor, "start");
    else if (t->ancora == 'm')
      strcpy(anchor, "middle");
    else
      strcpy(anchor, "end");

    fprintf(svg, "  <text x=\"%.2f\" y=\"%.2f\" text-anchor=\"%s\" stroke=\"%s\" fill=\"%s\">%s</text>\n",
            t->x, t->y, anchor, t->corb, t->corp, t->texto);
    break;
  }
  }
}

void escreve_forma_txt(Forma f, FILE *txt)
{
  FormaStr *forma = (FormaStr *)f;

  switch (forma->tipo)
  {
  case CIRCULO:
  {
    Circulo *c = (Circulo *)forma->dados;
    fprintf(txt, "Circulo id=%d centro=(%.2f,%.2f) raio=%.2f corb=%s corp=%s\n",
            c->id, c->x, c->y, c->r, c->corb, c->corp);
    break;
  }
  case RETANGULO:
  {
    Retangulo *r = (Retangulo *)forma->dados;
    fprintf(txt, "Retangulo id=%d ancora=(%.2f,%.2f) w=%.2f h=%.2f corb=%s corp=%s\n",
            r->id, r->x, r->y, r->w, r->h, r->corb, r->corp);
    break;
  }
  case LINHA:
  {
    Linha *l = (Linha *)forma->dados;
    fprintf(txt, "Linha id=%d p1=(%.2f,%.2f) p2=(%.2f,%.2f) cor=%s\n",
            l->id, l->x1, l->y1, l->x2, l->y2, l->cor);
    break;
  }
  case TEXTO:
  {
    Texto *t = (Texto *)forma->dados;
    fprintf(txt, "Texto id=%d ancora=(%.2f,%.2f) ancora=%c texto=\"%s\" corb=%s corp=%s\n",
            t->id, t->x, t->y, t->ancora, t->texto, t->corb, t->corp);
    break;
  }
  }
}

void destroy_forma(Forma f)
{
  FormaStr *forma = (FormaStr *)f;
  if (forma->dados)
    free(forma->dados);
  free(forma);
}

// Funções auxiliares para detecção de colisão
static int circulo_circulo(Circulo *c1, Circulo *c2)
{
  double dx = c1->x - c2->x;
  double dy = c1->y - c2->y;
  double dist = sqrt(dx * dx + dy * dy);
  return dist < (c1->r + c2->r);
}

static int ponto_em_retangulo(double px, double py, Retangulo *r)
{
  return px >= r->x && px <= r->x + r->w && py >= r->y && py <= r->y + r->h;
}

static int circulo_retangulo(Circulo *c, Retangulo *r)
{
  double closestX = fmax(r->x, fmin(c->x, r->x + r->w));
  double closestY = fmax(r->y, fmin(c->y, r->y + r->h));
  double dx = c->x - closestX;
  double dy = c->y - closestY;
  return (dx * dx + dy * dy) < (c->r * c->r);
}

static int retangulo_retangulo(Retangulo *r1, Retangulo *r2)
{
  return !(r1->x + r1->w < r2->x || r2->x + r2->w < r1->x ||
           r1->y + r1->h < r2->y || r2->y + r2->h < r1->y);
}

static void get_segmento_texto(Texto *t, double *x1, double *y1, double *x2, double *y2)
{
  int len = strlen(t->texto);
  double comprimento = 10.0 * len;

  if (t->ancora == 'i')
  {
    *x1 = t->x;
    *y1 = t->y;
    *x2 = t->x + comprimento;
    *y2 = t->y;
  }
  else if (t->ancora == 'f')
  {
    *x1 = t->x - comprimento;
    *y1 = t->y;
    *x2 = t->x;
    *y2 = t->y;
  }
  else
  { // 'm'
    *x1 = t->x - comprimento / 2;
    *y1 = t->y;
    *x2 = t->x + comprimento / 2;
    *y2 = t->y;
  }
}

static int segmento_circulo(double x1, double y1, double x2, double y2, Circulo *c)
{
  double dx = x2 - x1;
  double dy = y2 - y1;
  double len = sqrt(dx * dx + dy * dy);

  if (len == 0)
  {
    double dist = sqrt((x1 - c->x) * (x1 - c->x) + (y1 - c->y) * (y1 - c->y));
    return dist <= c->r;
  }

  double t = ((c->x - x1) * dx + (c->y - y1) * dy) / (len * len);
  t = fmax(0, fmin(1, t));

  double closestX = x1 + t * dx;
  double closestY = y1 + t * dy;
  double dist = sqrt((closestX - c->x) * (closestX - c->x) + (closestY - c->y) * (closestY - c->y));

  return dist <= c->r;
}

static int segmento_retangulo(double x1, double y1, double x2, double y2, Retangulo *r)
{
  if (ponto_em_retangulo(x1, y1, r) || ponto_em_retangulo(x2, y2, r))
    return 1;

  double rx2 = r->x + r->w;
  double ry2 = r->y + r->h;

  return (x1 <= rx2 && x2 >= r->x && y1 <= ry2 && y2 >= r->y);
}

int formas_sobrepoem(Forma f1, Forma f2)
{
  FormaStr *forma1 = (FormaStr *)f1;
  FormaStr *forma2 = (FormaStr *)f2;

  if (forma1->tipo == CIRCULO && forma2->tipo == CIRCULO)
  {
    return circulo_circulo((Circulo *)forma1->dados, (Circulo *)forma2->dados);
  }

  if (forma1->tipo == CIRCULO && forma2->tipo == RETANGULO)
  {
    return circulo_retangulo((Circulo *)forma1->dados, (Retangulo *)forma2->dados);
  }

  if (forma1->tipo == RETANGULO && forma2->tipo == CIRCULO)
  {
    return circulo_retangulo((Circulo *)forma2->dados, (Retangulo *)forma1->dados);
  }

  if (forma1->tipo == RETANGULO && forma2->tipo == RETANGULO)
  {
    return retangulo_retangulo((Retangulo *)forma1->dados, (Retangulo *)forma2->dados);
  }

  if (forma1->tipo == TEXTO || forma2->tipo == TEXTO)
  {
    double tx1, ty1, tx2, ty2;

    if (forma1->tipo == TEXTO)
    {
      get_segmento_texto((Texto *)forma1->dados, &tx1, &ty1, &tx2, &ty2);
      if (forma2->tipo == CIRCULO)
      {
        return segmento_circulo(tx1, ty1, tx2, ty2, (Circulo *)forma2->dados);
      }
      if (forma2->tipo == RETANGULO)
      {
        return segmento_retangulo(tx1, ty1, tx2, ty2, (Retangulo *)forma2->dados);
      }
    }

    if (forma2->tipo == TEXTO)
    {
      get_segmento_texto((Texto *)forma2->dados, &tx1, &ty1, &tx2, &ty2);
      if (forma1->tipo == CIRCULO)
      {
        return segmento_circulo(tx1, ty1, tx2, ty2, (Circulo *)forma1->dados);
      }
      if (forma1->tipo == RETANGULO)
      {
        return segmento_retangulo(tx1, ty1, tx2, ty2, (Retangulo *)forma1->dados);
      }
    }
  }

  return 0;
}