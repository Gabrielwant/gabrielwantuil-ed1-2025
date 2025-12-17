#include <stdlib.h>
#include <stdio.h>
#include "disparador.h"
#include "pilha.h"

typedef struct carregador
{
  int id;
  Pilha pilha;
} CarregadorStr;

typedef struct disparador
{
  int id;
  double x, y;
  CarregadorStr *esq;
  CarregadorStr *dir;
  Forma pos_disparo;
} DisparadorStr;

Carregador create_carregador(int id)
{
  CarregadorStr *c = (CarregadorStr *)malloc(sizeof(CarregadorStr));
  c->id = id;
  c->pilha = create_pilha();
  return c;
}

int get_id_carregador(Carregador c)
{
  CarregadorStr *carr = (CarregadorStr *)c;
  return carr->id;
}

void add_forma_carregador(Carregador c, Forma f)
{
  CarregadorStr *carr = (CarregadorStr *)c;
  push(carr->pilha, f);
}

Disparador create_disparador(int id, double x, double y)
{
  DisparadorStr *d = (DisparadorStr *)malloc(sizeof(DisparadorStr));
  d->id = id;
  d->x = x;
  d->y = y;
  d->esq = NULL;
  d->dir = NULL;
  d->pos_disparo = NULL;
  return d;
}

void attach_carregadores(Disparador d, Carregador esq, Carregador dir)
{
  DisparadorStr *disp = (DisparadorStr *)d;
  disp->esq = (CarregadorStr *)esq;
  disp->dir = (CarregadorStr *)dir;
}

Forma shift_disparador(Disparador d, char lado)
{
  DisparadorStr *disp = (DisparadorStr *)d;
  CarregadorStr *carr_origem = NULL;
  CarregadorStr *carr_destino = NULL;

  if (lado == 'd' || lado == 'D')
  {
    carr_origem = disp->dir;
    carr_destino = disp->esq;
  }
  else
  {
    carr_origem = disp->esq;
    carr_destino = disp->dir;
  }

  if (carr_origem == NULL || is_empty_pilha(carr_origem->pilha))
  {
    return disp->pos_disparo;
  }

  // Se já há forma em posição de disparo, move para o outro carregador
  if (disp->pos_disparo != NULL)
  {
    if (carr_destino != NULL)
    {
      push(carr_destino->pilha, disp->pos_disparo);
    }
  }

  // Pega forma do topo do carregador de origem
  disp->pos_disparo = (Forma)pop(carr_origem->pilha);

  return disp->pos_disparo;
}

Forma fire_disparador(Disparador d)
{
  DisparadorStr *disp = (DisparadorStr *)d;
  Forma f = disp->pos_disparo;
  disp->pos_disparo = NULL;
  return f;
}

double get_x_disparador(Disparador d)
{
  DisparadorStr *disp = (DisparadorStr *)d;
  return disp->x;
}

double get_y_disparador(Disparador d)
{
  DisparadorStr *disp = (DisparadorStr *)d;
  return disp->y;
}

Forma get_forma_disparo(Disparador d)
{
  DisparadorStr *disp = (DisparadorStr *)d;
  return disp->pos_disparo;
}

int is_empty_carregador(Carregador c)
{
  CarregadorStr *carr = (CarregadorStr *)c;
  return is_empty_pilha(carr->pilha);
}

void destroy_carregador(Carregador c)
{
  CarregadorStr *carr = (CarregadorStr *)c;
  destroy_pilha(carr->pilha);
  free(carr);
}

void destroy_disparador(Disparador d)
{
  DisparadorStr *disp = (DisparadorStr *)d;
  free(disp);
}