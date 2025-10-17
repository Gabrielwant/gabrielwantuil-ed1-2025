#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "formas.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct forma
{
    int id;
    char tipo;
    double x, y, w, h, r;
    char corb[30], corp[30];
};

Forma *criaCirculo(int id, double x, double y, double r, const char *corb, const char *corp)
{
    Forma *f = malloc(sizeof(Forma));
    f->id = id;
    f->tipo = 'c';
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
    f->id = id;
    f->tipo = 'r';
    f->x = x;
    f->y = y;
    f->w = w;
    f->h = h;
    strcpy(f->corb, corb);
    strcpy(f->corp, corp);
    return f;
}

void liberaForma(Forma *f)
{
    free(f);
}

void escreveCirculoSVG(FILE *svg, Forma *f)
{
    fprintf(svg, "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" fill=\"%s\" stroke=\"%s\" />\n",
            f->x, f->y, f->r, f->corp, f->corb);
}

void escreveRetanguloSVG(FILE *svg, Forma *f)
{
    fprintf(svg, "<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" fill=\"%s\" stroke=\"%s\" />\n",
            f->x, f->y, f->w, f->h, f->corp, f->corb);
}

void desenhaForma(FILE *svg, Forma *f)
{
    if (f->tipo == 'c')
        escreveCirculoSVG(svg, f);
    else
        escreveRetanguloSVG(svg, f);
}

double areaForma(Forma *f)
{
    if (f->tipo == 'c')
        return M_PI * f->r * f->r;
    return f->w * f->h;
}

int sobrepoe(Forma *a, Forma *b)
{
    if (a->tipo == 'c' && b->tipo == 'c')
    {
        double dx = a->x - b->x, dy = a->y - b->y;
        double dist = sqrt(dx * dx + dy * dy);
        return dist < (a->r + b->r);
    }
    if (a->tipo == 'r' && b->tipo == 'r')
    {
        return !(a->x + a->w < b->x || b->x + b->w < a->x || a->y + a->h < b->y || b->y + b->h < a->y);
    }

    Forma *c = (a->tipo == 'c') ? a : b;
    Forma *r = (a->tipo == 'r') ? a : b;
    double cx = c->x, cy = c->y;
    double closestX = fmax(r->x, fmin(cx, r->x + r->w));
    double closestY = fmax(r->y, fmin(cy, r->y + r->h));
    double dx = cx - closestX, dy = cy - closestY;
    return (dx * dx + dy * dy) < (c->r * c->r);
}

Forma *clonaForma(Forma *orig)
{
    Forma *f = malloc(sizeof(Forma));
    memcpy(f, orig, sizeof(Forma));
    return f;
}

void trocaCores(Forma *f)
{
    char tmp[30];
    strcpy(tmp, f->corb);
    strcpy(f->corb, f->corp);
    strcpy(f->corp, tmp);
}

void mudaCorBorda(Forma *f, const char *novaCor)
{
    strcpy(f->corb, novaCor);
}

const char *getCorPreenchimento(Forma *f)
{
    return f->corp;
}
