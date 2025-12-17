#ifndef PILHA_H
#define PILHA_H

/*
 * TAD Pilha - Tipo Abstrato de Dados Pilha
 * Implementação de pilha genérica usando ponteiros void*
 */

typedef void *Pilha;

/*
 * Cria uma nova pilha vazia
 * Retorna: ponteiro para a pilha criada
 */
Pilha create_pilha();

/*
 * Insere um elemento no topo da pilha
 * Parâmetros:
 *   p: pilha onde será inserido
 *   info: ponteiro para o dado a ser inserido
 */
void push(Pilha p, void *info);

/*
 * Remove e retorna o elemento do topo da pilha
 * Parâmetros:
 *   p: pilha de onde será removido
 * Retorna: ponteiro para o dado removido
 */
void *pop(Pilha p);

/*
 * Retorna o elemento do topo da pilha sem removê-lo
 * Parâmetros:
 *   p: pilha a ser consultada
 * Retorna: ponteiro para o dado do topo
 */
void *top(Pilha p);

/*
 * Verifica se a pilha está vazia
 * Parâmetros:
 *   p: pilha a ser verificada
 * Retorna: 1 se vazia, 0 caso contrário
 */
int is_empty_pilha(Pilha p);

/*
 * Retorna o número de elementos na pilha
 * Parâmetros:
 *   p: pilha a ser consultada
 * Retorna: número de elementos
 */
int size_pilha(Pilha p);

/*
 * Libera toda a memória da pilha
 * Parâmetros:
 *   p: pilha a ser liberada
 */
void destroy_pilha(Pilha p);

#endif