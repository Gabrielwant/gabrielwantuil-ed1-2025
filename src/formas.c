#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "formas.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct forma
{
    int id;
    char tipo;
    double x, y, w, h, r;
    double x2, y2;
    char corb[30], corp[30];
    char ancora;
    char texto[256];
} Forma;

static double dist2(double x1, double y1, double x2, double y2)
{
    double dx = x1 - x2, dy = y1 - y2;
    return dx * dx + dy * dy;
}
static double clamp(double v, double a, double b) { return v < a ? a : (v > b ? b : v); }

Forma *criaCirculo(int id, double x, double y, double r, const char *corb, const char *corp)
{
    Forma *f = malloc(sizeof(Forma));
    f->id = id;
    f->tipo = 'c';
    f->x = x;
    f->y = y;
    f->r = r;
    f->w = f->h = 0;
    f->x2 = f->y2 = 0;
    strcpy(f->corb, corb);
    strcpy(f->corp, corp);
    f->ancora = 'i';
    f->texto[0] = '\0';
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
    f->r = 0;
    f->x2 = f->y2 = 0;
    strcpy(f->corb, corb);
    strcpy(f->corp, corp);
    f->ancora = 'i';
    f->texto[0] = '\0';
    return f;
}
Forma *criaLinha(int id, double x1, double y1, double x2, double y2, const char *cor)
{
    Forma *f = malloc(sizeof(Forma));
    f->id = id;
    f->tipo = 'l';
    f->x = x1;
    f->y = y1;
    f->x2 = x2;
    f->y2 = y2;
    f->w = f->h = f->r = 0;
    strcpy(f->corb, cor);
    strcpy(f->corp, "none");
    f->ancora = 'i';
    f->texto[0] = '\0';
    return f;
}
Forma *criaTexto(int id, double x, double y, const char *corb, const char *corp, char ancora, const char *txt)
{
    Forma *f = malloc(sizeof(Forma));
    f->id = id;
    f->tipo = 't';
    f->x = x;
    f->y = y;
    f->w = f->h = f->r = 0;
    f->x2 = f->y2 = 0;
    strcpy(f->corb, corb);
    strcpy(f->corp, corp);
    f->ancora = ancora;
    strncpy(f->texto, txt ? txt : "", sizeof(f->texto) - 1);
    f->texto[sizeof(f->texto) - 1] = '\0';
    return f;
}

void liberaForma(Forma *f) { free(f); }

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
void escreveLinhaSVG(FILE *svg, Forma *f)
{
    fprintf(svg, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\" />\n",
            f->x, f->y, f->x2, f->y2, f->corb);
}
static const char *mapWeight(const char *w)
{
    if (!w)
        return "normal";
    if (strcmp(w, "n") == 0)
        return "normal";
    if (strcmp(w, "b") == 0)
        return "bold";
    if (strcmp(w, "b+") == 0)
        return "bolder";
    if (strcmp(w, "l") == 0)
        return "lighter";
    return w;
}
static const char *mapAnchor(char a)
{
    if (a == 'i')
        return "start";
    if (a == 'm')
        return "middle";
    if (a == 'f')
        return "end";
    return "start";
}
void escreveTextoSVG(FILE *svg, Forma *f, const char *fontFamily, const char *fontWeight, double fontSize)
{
    fprintf(svg,
            "<text x=\"%.2f\" y=\"%.2f\" fill=\"%s\" stroke=\"%s\" font-family=\"%s\" font-weight=\"%s\" font-size=\"%.1f\" text-anchor=\"%s\">%s</text>\n",
            f->x, f->y, f->corp, f->corb, fontFamily ? fontFamily : "sans", mapWeight(fontWeight), fontSize > 0 ? fontSize : 12.0, mapAnchor(f->ancora), f->texto);
}

void desenhaForma(FILE *svg, Forma *f)
{
    if (f->tipo == 'c')
        escreveCirculoSVG(svg, f);
    else if (f->tipo == 'r')
        escreveRetanguloSVG(svg, f);
    else if (f->tipo == 'l')
        escreveLinhaSVG(svg, f);
    else
        escreveTextoSVG(svg, f, "sans", "n", 12.0);
}

double areaForma(Forma *f)
{
    if (f->tipo == 'c')
        return M_PI * f->r * f->r;
    if (f->tipo == 'r')
        return f->w * f->h;
    if (f->tipo == 'l')
    {
        double len = sqrt((f->x2 - f->x) * (f->x2 - f->x) + (f->y2 - f->y) * (f->y2 - f->y));
        return 2.0 * len;
    }
    return 20.0 * (double)strlen(f->texto);
}

static double distPontoSegmento(double px, double py, double x1, double y1, double x2, double y2)
{
    double L2 = dist2(x1, y1, x2, y2);
    if (L2 == 0)
        return sqrt(dist2(px, py, x1, y1));
    double t = ((px - x1) * (x2 - x1) + (py - y1) * (y2 - y1)) / L2;
    t = clamp(t, 0, 1);
    double projx = x1 + t * (x2 - x1);
    double projy = y1 + t * (y2 - y1);
    return sqrt(dist2(px, py, projx, projy));
}
static int segIntersec(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
    double d1 = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
    double d2 = (x4 - x3) * (y2 - y3) - (y4 - y3) * (x2 - x3);
    double d3 = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
    double d4 = (x2 - x1) * (y4 - y1) - (y2 - y1) * (x4 - x1);
    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
        return 1;
    return 0;
}
static void textoSegmento(Forma *t, double *x1, double *y1, double *x2, double *y2)
{
    int n = (int)strlen(t->texto);
    if (t->ancora == 'i')
    {
        *x1 = t->x;
        *y1 = t->y;
        *x2 = t->x + 10.0 * n;
        *y2 = t->y;
    }
    else if (t->ancora == 'f')
    {
        *x1 = t->x - 10.0 * n;
        *y1 = t->y;
        *x2 = t->x;
        *y2 = t->y;
    }
    else
    {
        *x1 = t->x - 10.0 * n / 2.0;
        *y1 = t->y;
        *x2 = t->x + 10.0 * n / 2.0;
        *y2 = t->y;
    }
}

int sobrepoe(Forma *a, Forma *b)
{
    if (a->tipo == 'c' && b->tipo == 'c')
    {
        double dist = sqrt(dist2(a->x, a->y, b->x, b->y));
        return dist < (a->r + b->r);
    }
    if (a->tipo == 'r' && b->tipo == 'r')
    {
        return !(a->x + a->w < b->x || b->x + b->w < a->x || a->y + a->h < b->y || b->y + b->h < a->y);
    }
    if ((a->tipo == 'c' && b->tipo == 'r') || (a->tipo == 'r' && b->tipo == 'c'))
    {
        Forma *c = (a->tipo == 'c') ? a : b;
        Forma *r = (a->tipo == 'r') ? a : b;
        double cx = c->x, cy = c->y;
        double closestX = clamp(cx, r->x, r->x + r->w);
        double closestY = clamp(cy, r->y, r->y + r->h);
        return dist2(cx, cy, closestX, closestY) < c->r * c->r;
    }
    if (a->tipo == 'l' || b->tipo == 'l')
    {
        Forma *L = (a->tipo == 'l') ? a : b;
        Forma *O = (a->tipo == 'l') ? b : a;
        if (O->tipo == 'l')
            return segIntersec(L->x, L->y, L->x2, L->y2, O->x, O->y, O->x2, O->y2);
        if (O->tipo == 'r')
        {
            double x1 = O->x, y1 = O->y, x2 = O->x + O->w, y2 = O->y + O->h;
            if (segIntersec(L->x, L->y, L->x2, L->y2, x1, y1, x2, y1))
                return 1;
            if (segIntersec(L->x, L->y, L->x2, L->y2, x2, y1, x2, y2))
                return 1;
            if (segIntersec(L->x, L->y, L->x2, L->y2, x2, y2, x1, y2))
                return 1;
            if (segIntersec(L->x, L->y, L->x2, L->y2, x1, y2, x1, y1))
                return 1;
            return (L->x > O->x && L->x < O->x + O->w && L->y > O->y && L->y < O->y + O->h);
        }
        if (O->tipo == 'c')
            return distPontoSegmento(O->x, O->y, L->x, L->y, L->x2, L->y2) <= O->r;
        double tx1, ty1, tx2, ty2;
        textoSegmento(O, &tx1, &ty1, &tx2, &ty2);
        return segIntersec(L->x, L->y, L->x2, L->y2, tx1, ty1, tx2, ty2);
    }
    if (a->tipo == 't' || b->tipo == 't')
    {
        Forma *T = (a->tipo == 't') ? a : b;
        Forma *O = (a->tipo == 't') ? b : a;
        double tx1, ty1, tx2, ty2;
        textoSegmento(T, &tx1, &ty1, &tx2, &ty2);
        if (O->tipo == 'c')
            return distPontoSegmento(O->x, O->y, tx1, ty1, tx2, ty2) <= O->r;
        if (O->tipo == 'r')
        {
            double x1 = O->x, y1 = O->y, x2 = O->x + O->w, y2 = O->y + O->h;
            if (segIntersec(tx1, ty1, tx2, ty2, x1, y1, x2, y1))
                return 1;
            if (segIntersec(tx1, ty1, tx2, ty2, x2, y1, x2, y2))
                return 1;
            if (segIntersec(tx1, ty1, tx2, ty2, x2, y2, x1, y2))
                return 1;
            if (segIntersec(tx1, ty1, tx2, ty2, x1, y2, x1, y1))
                return 1;
            return (T->x > O->x && T->x < O->x + O->w && T->y > O->y && T->y < O->y + O->h);
        }
        double ux1, uy1, ux2, uy2;
        textoSegmento(O, &ux1, &uy1, &ux2, &uy2);
        return segIntersec(tx1, ty1, tx2, ty2, ux1, uy1, ux2, uy2);
    }
    return 0;
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
void mudaCorBorda(Forma *f, const char *novaCor) { strcpy(f->corb, novaCor); }
const char *getCorPreenchimento(Forma *f) { return f->corp; }
