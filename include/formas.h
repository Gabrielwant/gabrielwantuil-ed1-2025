#ifndef FORMAS_H
#define FORMAS_H
#include <stdio.h>

typedef struct forma Forma;
Forma *criaCirculo(int id, double x, double y, double r, const char *corb, const char *corp);
Forma *criaRetangulo(int id, double x, double y, double w, double h, const char *corb, const char *corp);
Forma *criaLinha(int id, double x1, double y1, double x2, double y2, const char *cor);
Forma *criaTexto(int id, double x, double y, const char *corb, const char *corp, char ancora, const char *txt);
void liberaForma(Forma *f);
void escreveCirculoSVG(FILE *svg, Forma *f);
void escreveRetanguloSVG(FILE *svg, Forma *f);
void escreveLinhaSVG(FILE *svg, Forma *f);
void escreveTextoSVG(FILE *svg, Forma *f, const char *fontFamily, const char *fontWeight, double fontSize);
void desenhaForma(FILE *svg, Forma *f);
void mudaCorBorda(Forma *f, const char *novaCor);
void trocaCores(Forma *f);
const char *getCorPreenchimento(Forma *f);
double areaForma(Forma *f);
int sobrepoe(Forma *a, Forma *b);
Forma *clonaForma(Forma *orig);
#endif
