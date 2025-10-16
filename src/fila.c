#include <stdlib.h>
#include "fila.h"

struct fila
{
    int inicio;
    int fim;
    int tamanho;
    int capacidade;
    void **dados;
};

Fila *criaFila()
{
    Fila *f = malloc(sizeof(Fila));
    if (!f)
        return NULL;
    f->capacidade = 10;
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    f->dados = malloc(sizeof(void *) * f->capacidade);
    if (!f->dados)
    {
        free(f);
        return NULL;
    }
    return f;
}

void liberaFila(Fila *f)
{
    if (!f)
        return;
    free(f->dados);
    free(f);
}

int filaVazia(Fila *f)
{
    return f == NULL || f->tamanho == 0;
}

int insereFila(Fila *f, void *elem)
{
    if (!f)
        return 0;
    if (f->tamanho == f->capacidade)
    {
        int novaCap = f->capacidade * 2;
        void **novo = realloc(f->dados, sizeof(void *) * novaCap);
        if (!novo)
            return 0;
        f->dados = novo;
        f->capacidade = novaCap;
    }
    f->dados[f->fim] = elem;
    f->fim = (f->fim + 1) % f->capacidade;
    f->tamanho++;
    return 1;
}

void *removeFila(Fila *f)
{
    if (!f || f->tamanho == 0)
        return NULL;
    void *elem = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return elem;
}

void *frenteFila(Fila *f)
{
    if (!f || f->tamanho == 0)
        return NULL;
    return f->dados[f->inicio];
}

int tamanhoFila(Fila *f)
{
    if (!f)
        return 0;
    return f->tamanho;
}
