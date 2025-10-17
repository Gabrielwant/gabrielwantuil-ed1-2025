#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formas.h"

struct forma
{
    char tipo; // 'c' ou 'r'
    int id;
    double x, y, w, h, r;
    char corb[30];
    char corp[30];
};

Forma *criaCirculo(int id, double x, double y, double r, const char *corb, const char *corp)
{
    Forma *f = malloc(sizeof(Forma));
    if (!f)
        return NULL;
    f->tipo = 'c';
    f->id = id;
    f->x = x;
    f->y = y;
    f->r = r;
    strcpy(f->corb, corb);
    strcpy(f->corp, corp);
    return f;
}

Forma *criaRetangulo(int id, double x, double y, double w, double h, const char *corb, const char *corp)
{
    Forma *f = malloc(sizeof(Forma));
    if (!f)
        return NULL;
    f->tipo = 'r';
    f->id = id;
    f->x = x;
    f->y = y;
    f->w = w;
    f->h = h;
    strcpy(f->corb, corb);
    strcpy(f->corp, corp);
    return f;
}

void imprimeForma(Forma *f)
{
    if (f->tipo == 'c')
        printf("Circulo %d: centro(%.2f, %.2f) raio %.2f corb=%s corp=%s\n",
               f->id, f->x, f->y, f->r, f->corb, f->corp);
    else if (f->tipo == 'r')
        printf("Retangulo %d: pos(%.2f, %.2f) w=%.2f h=%.2f corb=%s corp=%s\n",
               f->id, f->x, f->y, f->w, f->h, f->corb, f->corp);
}

void liberaForma(Forma *f)
{
    free(f);
}

void escreveCirculoSVG(FILE *svg, Forma *f)
{
    fprintf(svg, "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" stroke=\"%s\" fill=\"%s\" />\n",
            f->x, f->y, f->r, f->corb, f->corp);
}

void escreveRetanguloSVG(FILE *svg, Forma *f)
{
    fprintf(svg, "<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" stroke=\"%s\" fill=\"%s\" />\n",
            f->x, f->y, f->w, f->h, f->corb, f->corp);
}
