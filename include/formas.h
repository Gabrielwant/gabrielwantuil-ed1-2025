#ifndef FORMAS_H
#define FORMAS_H
#include <stdio.h>

typedef struct forma Forma;

// criação
Forma *criaCirculo(int id, double x, double y, double r, const char *corb, const char *corp);
Forma *criaRetangulo(int id, double x, double y, double w, double h, const char *corb, const char *corp);
Forma *criaLinha(int id, double x1, double y1, double x2, double y2, const char *cor);
Forma *criaTexto(int id, double x, double y, const char *corb, const char *corp, char ancora, const char *txt);

// liberação
void liberaForma(Forma *f);

// desenho
void escreveCirculoSVG(FILE *svg, Forma *f);
void escreveRetanguloSVG(FILE *svg, Forma *f);
void escreveLinhaSVG(FILE *svg, Forma *f);
void escreveTextoSVG(FILE *svg, Forma *f, const char *fontFamily, const char *fontWeight, double fontSize);
void desenhaForma(FILE *svg, Forma *f);

// propriedades/estilo
void mudaCorBorda(Forma *f, const char *novaCor);
void trocaCores(Forma *f);
const char *getCorPreenchimento(Forma *f);

// utilidades (arena)
double areaForma(Forma *f);       // c: πr²; r: w*h; l: 2*comprimento; t: 20*|texto|
int sobrepoe(Forma *a, Forma *b); // inclui linha e texto conforme PDF
Forma *clonaForma(Forma *orig);

#endif
