#ifndef FORMAS_H
#define FORMAS_H

typedef struct forma Forma;

Forma *criaCirculo(int id, double x, double y, double r, const char *corb, const char *corp);
Forma *criaRetangulo(int id, double x, double y, double w, double h, const char *corb, const char *corp);
void imprimeForma(Forma *f);
void liberaForma(Forma *f);

#endif
