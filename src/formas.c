#include <stdlib.h>
#include <string.h>
#include "formas.h"
struct forma {
    int id;
    int tipo;
    double x1;
    double y1;
    double x2;
    double y2;
    double r;
    double w;
    double h;
    char* corb;
    char* corp;
    char* texto;
    char pos;
};
static char* duplica(const char* s){
    if(!s) return NULL;
    char* r = malloc(strlen(s)+1);
    if(!r) return NULL;
    strcpy(r,s);
    return r;
}
Forma* criaCirculo(int id, double x, double y, double r_, const char* corb, const char* corp){
    Forma* f = malloc(sizeof(Forma));
    if(!f) return NULL;
    f->id = id;
    f->tipo = 1;
    f->x1 = x;
    f->y1 = y;
    f->r = r_;
    f->corb = duplica(corb);
    f->corp = duplica(corp);
    f->texto = NULL;
    return f;
}
Forma* criaRetangulo(int id, double x, double y, double w, double h, const char* corb, const char* corp){
    Forma* f = malloc(sizeof(Forma));
    if(!f) return NULL;
    f->id = id;
    f->tipo = 2;
    f->x1 = x;
    f->y1 = y;
    f->w = w;
    f->h = h;
    f->corb = duplica(corb);
    f->corp = duplica(corp);
    f->texto = NULL;
    return f;
}
Forma* criaLinha(int id, double x1, double y1, double x2, double y2, const char* cor){
    Forma* f = malloc(sizeof(Forma));
    if(!f) return NULL;
    f->id = id;
    f->tipo = 3;
    f->x1 = x1;
    f->y1 = y1;
    f->x2 = x2;
    f->y2 = y2;
    f->corb = duplica(cor);
    f->corp = NULL;
    f->texto = NULL;
    return f;
}
Forma* criaTexto(int id, double x, double y, const char* corb, const char* corp, char pos, const char* txt){
    Forma* f = malloc(sizeof(Forma));
    if(!f) return NULL;
    f->id = id;
    f->tipo = 4;
    f->x1 = x;
    f->y1 = y;
    f->pos = pos;
    f->corb = duplica(corb);
    f->corp = duplica(corp);
    f->texto = duplica(txt);
    return f;
}
double areaForma(Forma* f){
    if(!f) return 0.0;
    if(f->tipo == 1) return 3.14159265358979323846 * f->r * f->r;
    if(f->tipo == 2) return f->w * f->h;
    if(f->tipo == 4) return 20.0 * (f->texto ? strlen(f->texto) : 0);
    if(f->tipo == 3) {
        double dx = f->x2 - f->x1;
        double dy = f->y2 - f->y1;
        double len = sqrt(dx*dx + dy*dy);
        return 2.0 * len;
    }
    return 0.0;
}
int sobreposicao(Forma* a, Forma* b){
    (void)a; (void)b;
    return 0;
}
void liberaForma(Forma* f){
    if(!f) return;
    if(f->corb) free(f->corb);
    if(f->corp) free(f->corp);
    if(f->texto) free(f->texto);
    free(f);
}
