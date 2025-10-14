#ifndef FORMAS_H
#define FORMAS_H
typedef struct forma Forma;
Forma* criaCirculo(int id, double x, double y, double r, const char* corb, const char* corp);
Forma* criaRetangulo(int id, double x, double y, double w, double h, const char* corb, const char* corp);
Forma* criaLinha(int id, double x1, double y1, double x2, double y2, const char* cor);
Forma* criaTexto(int id, double x, double y, const char* corb, const char* corp, char pos, const char* txt);
double areaForma(Forma* f);
int sobreposicao(Forma* a, Forma* b);
void liberaForma(Forma* f);
#endif
