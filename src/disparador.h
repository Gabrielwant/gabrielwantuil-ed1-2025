#ifndef DISPARADOR_H
#define DISPARADOR_H

#include "forma.h"

/*
 * TAD Disparador - Sistema de disparo com carregadores
 */

typedef void *Disparador;
typedef void *Carregador;

/*
 * Cria um novo carregador vazio
 */
Carregador create_carregador(int id);

/*
 * Retorna o ID do carregador
 */
int get_id_carregador(Carregador c);

/*
 * Adiciona uma forma ao carregador
 */
void add_forma_carregador(Carregador c, Forma f);

/*
 * Cria um novo disparador
 */
Disparador create_disparador(int id, double x, double y);

/*
 * Encaixa carregadores no disparador
 */
void attach_carregadores(Disparador d, Carregador esq, Carregador dir);

/*
 * Pressiona botão de seleção (move forma para posição de disparo)
 * lado: 'e' para esquerdo, 'd' para direito
 * Retorna: forma que ficou em posição de disparo (ou NULL)
 */
Forma shift_disparador(Disparador d, char lado);

/*
 * Dispara a forma que está em posição de disparo
 * Retorna: forma disparada (ou NULL se não havia forma)
 */
Forma fire_disparador(Disparador d);

/*
 * Obtém a posição X do disparador
 */
double get_x_disparador(Disparador d);

/*
 * Obtém a posição Y do disparador
 */
double get_y_disparador(Disparador d);

/*
 * Obtém a forma em posição de disparo
 */
Forma get_forma_disparo(Disparador d);

/*
 * Verifica se carregador está vazio
 */
int is_empty_carregador(Carregador c);

/*
 * Libera memória do carregador
 */
void destroy_carregador(Carregador c);

/*
 * Libera memória do disparador
 */
void destroy_disparador(Disparador d);

#endif