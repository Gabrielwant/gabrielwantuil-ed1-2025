#ifndef FORMA_H
#define FORMA_H

/*
 * TAD Forma - Representa formas geométricas
 * Tipos: círculo, retângulo, linha, texto
 */

typedef void *Forma;

typedef enum
{
  CIRCULO,
  RETANGULO,
  LINHA,
  TEXTO
} TipoForma;

/*
 * Cria um círculo
 * Parâmetros:
 *   id: identificador único
 *   x, y: coordenadas do centro
 *   r: raio
 *   corb: cor da borda
 *   corp: cor de preenchimento
 * Retorna: ponteiro para a forma criada
 */
Forma create_circulo(int id, double x, double y, double r,
                     char *corb, char *corp);

/*
 * Cria um retângulo
 * Parâmetros:
 *   id: identificador único
 *   x, y: coordenadas do canto inferior esquerdo
 *   w: largura
 *   h: altura
 *   corb: cor da borda
 *   corp: cor de preenchimento
 * Retorna: ponteiro para a forma criada
 */
Forma create_retangulo(int id, double x, double y, double w, double h,
                       char *corb, char *corp);

/*
 * Cria uma linha
 * Parâmetros:
 *   id: identificador único
 *   x1, y1: primeira extremidade
 *   x2, y2: segunda extremidade
 *   cor: cor da linha
 * Retorna: ponteiro para a forma criada
 */
Forma create_linha(int id, double x1, double y1, double x2, double y2,
                   char *cor);

/*
 * Cria um texto
 * Parâmetros:
 *   id: identificador único
 *   x, y: coordenadas da âncora
 *   corb: cor da borda
 *   corp: cor de preenchimento
 *   ancora: posição da âncora ('i', 'm', 'f')
 *   texto: string do texto
 * Retorna: ponteiro para a forma criada
 */
Forma create_texto(int id, double x, double y, char *corb, char *corp,
                   char ancora, char *texto);

/*
 * Clona uma forma, criando uma cópia com cores invertidas
 * Parâmetros:
 *   f: forma a ser clonada
 *   novo_id: identificador para o clone
 * Retorna: ponteiro para a forma clonada
 */
Forma clone_forma(Forma f, int novo_id);

/*
 * Retorna o tipo da forma
 */
TipoForma get_tipo_forma(Forma f);

/*
 * Retorna o identificador da forma
 */
int get_id_forma(Forma f);

/*
 * Retorna a área da forma
 */
double get_area_forma(Forma f);

/*
 * Verifica se duas formas se sobrepõem
 * Retorna: 1 se há sobreposição, 0 caso contrário
 */
int formas_sobrepoem(Forma f1, Forma f2);

/*
 * Muda a cor da borda de uma forma
 */
void set_cor_borda_forma(Forma f, char *nova_cor);

/*
 * Obtém a cor da borda
 */
char *get_cor_borda_forma(Forma f);

/*
 * Obtém a cor de preenchimento
 */
char *get_cor_preenchimento_forma(Forma f);

/*
 * Move a forma para uma nova posição
 */
void move_forma(Forma f, double novo_x, double novo_y);

/*
 * Obtém a posição X da âncora
 */
double get_x_forma(Forma f);

/*
 * Obtém a posição Y da âncora
 */
double get_y_forma(Forma f);

/*
 * Escreve a forma no arquivo SVG
 */
void escreve_forma_svg(Forma f, FILE *svg);

/*
 * Escreve os dados da forma no arquivo TXT
 */
void escreve_forma_txt(Forma f, FILE *txt);

/*
 * Libera memória da forma
 */
void destroy_forma(Forma f);

#endif