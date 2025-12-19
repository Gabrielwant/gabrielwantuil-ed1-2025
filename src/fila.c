#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

typedef struct no
{
  void *dado;
  struct no *prox;
} No;

typedef struct fila
{
  No *inicio;
  No *fim;
  int tamanho;
} FilaStr;

Fila create_fila()
{
  FilaStr *f = (FilaStr *)malloc(sizeof(FilaStr));
  f->inicio = NULL;
  f->fim = NULL;
  f->tamanho = 0;
  return f;
}

void enqueue(Fila f, void *info)
{
  FilaStr *fila = (FilaStr *)f;
  No *novo = (No *)malloc(sizeof(No));
  novo->dado = info;
  novo->prox = NULL;

  if (fila->fim == NULL)
  {
    fila->inicio = novo;
    fila->fim = novo;
  }
  else
  {
    fila->fim->prox = novo;
    fila->fim = novo;
  }
  fila->tamanho++;
}

void *dequeue(Fila f)
{
  FilaStr *fila = (FilaStr *)f;
  if (fila->inicio == NULL)
  {
    return NULL;
  }

  No *temp = fila->inicio;
  void *dado = temp->dado;
  fila->inicio = fila->inicio->prox;

  if (fila->inicio == NULL)
  {
    fila->fim = NULL;
  }

  free(temp);
  fila->tamanho--;
  return dado;
}

void *front(Fila f)
{
  FilaStr *fila = (FilaStr *)f;
  if (fila->inicio == NULL)
  {
    return NULL;
  }
  return fila->inicio->dado;
}

int is_empty_fila(Fila f)
{
  FilaStr *fila = (FilaStr *)f;
  return fila->inicio == NULL;
}

int size_fila(Fila f)
{
  FilaStr *fila = (FilaStr *)f;
  return fila->tamanho;
}

void destroy_fila(Fila f)
{
  FilaStr *fila = (FilaStr *)f;
  while (!is_empty_fila(f))
  {
    dequeue(f);
  }
  free(fila);
}

Posic get_first_fila(Fila f)
{
  FilaStr *fila = (FilaStr *)f;
  return fila->inicio;
}

Posic get_next_fila(Fila f, Posic p)
{
  (void)f; // Silencia warning de parâmetro não usado
  No *no = (No *)p;
  if (no == NULL)
    return NULL;
  return no->prox;
}

void *get_data_fila(Fila f, Posic p)
{
  (void)f; // Silencia warning de parâmetro não usado
  No *no = (No *)p;
  if (no == NULL)
    return NULL;
  return no->dado;
}