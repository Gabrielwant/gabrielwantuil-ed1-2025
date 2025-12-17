#ifndef FILA_H
#define FILA_H

/*
 * TAD Fila - Tipo Abstrato de Dados Fila
 * Implementação de fila genérica usando ponteiros void*
 */

typedef void *Fila;
typedef void *Posic;

/*
 * Cria uma nova fila vazia
 * Retorna: ponteiro para a fila criada
 */
Fila create_fila();

/*
 * Insere um elemento no final da fila
 * Parâmetros:
 *   f: fila onde será inserido
 *   info: ponteiro para o dado a ser inserido
 */
void enqueue(Fila f, void *info);

/*
 * Remove e retorna o elemento do início da fila
 * Parâmetros:
 *   f: fila de onde será removido
 * Retorna: ponteiro para o dado removido
 */
void *dequeue(Fila f);

/*
 * Retorna o elemento do início da fila sem removê-lo
 * Parâmetros:
 *   f: fila a ser consultada
 * Retorna: ponteiro para o dado do início
 */
void *front(Fila f);

/*
 * Verifica se a fila está vazia
 * Parâmetros:
 *   f: fila a ser verificada
 * Retorna: 1 se vazia, 0 caso contrário
 */
int is_empty_fila(Fila f);

/*
 * Retorna o número de elementos na fila
 * Parâmetros:
 *   f: fila a ser consultada
 * Retorna: número de elementos
 */
int size_fila(Fila f);

/*
 * Libera toda a memória da fila
 * Parâmetros:
 *   f: fila a ser liberada
 */
void destroy_fila(Fila f);

/*
 * Retorna a primeira posição da fila (para iteração)
 * Parâmetros:
 *   f: fila a ser iterada
 * Retorna: primeira posição ou NULL se vazia
 */
Posic get_first_fila(Fila f);

/*
 * Retorna a próxima posição na fila
 * Parâmetros:
 *   f: fila sendo iterada
 *   p: posição atual
 * Retorna: próxima posição ou NULL se fim
 */
Posic get_next_fila(Fila f, Posic p);

/*
 * Retorna o dado em uma posição específica
 * Parâmetros:
 *   f: fila
 *   p: posição
 * Retorna: ponteiro para o dado
 */
void *get_data_fila(Fila f, Posic p);

#endif