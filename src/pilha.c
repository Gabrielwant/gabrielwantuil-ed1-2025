#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

typedef struct no
{
  void *dado;
  struct no *prox;
} No;

typedef struct pilha
{
  No *topo;
  int tamanho;
} PilhaStr;

Pilha create_pilha()
{
  PilhaStr *p = (PilhaStr *)malloc(sizeof(PilhaStr));
  p->topo = NULL;
  p->tamanho = 0;
  return p;
}

void push(Pilha p, void *info)
{
  PilhaStr *pilha = (PilhaStr *)p;
  No *novo = (No *)malloc(sizeof(No));
  novo->dado = info;
  novo->prox = pilha->topo;
  pilha->topo = novo;
  pilha->tamanho++;
}

void *pop(Pilha p)
{
  PilhaStr *pilha = (PilhaStr *)p;
  if (pilha->topo == NULL)
  {
    return NULL;
  }

  No *temp = pilha->topo;
  void *dado = temp->dado;
  pilha->topo = pilha->topo->prox;
  free(temp);
  pilha->tamanho--;
  return dado;
}

void *top(Pilha p)
{
  PilhaStr *pilha = (PilhaStr *)p;
  if (pilha->topo == NULL)
  {
    return NULL;
  }
  return pilha->topo->dado;
}

int is_empty_pilha(Pilha p)
{
  PilhaStr *pilha = (PilhaStr *)p;
  return pilha->topo == NULL;
}

int size_pilha(Pilha p)
{
  PilhaStr *pilha = (PilhaStr *)p;
  return pilha->tamanho;
}

void destroy_pilha(Pilha p)
{
  PilhaStr *pilha = (PilhaStr *)p;
  while (!is_empty_pilha(p))
  {
    pop(p);
  }
  free(pilha);
}