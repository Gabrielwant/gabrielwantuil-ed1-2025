
#ifndef FORMAS_H
#define FORMAS_H
typedef struct forma* Forma;
typedef struct banco* Banco;
Banco criaBanco(void);
void destroiBanco(Banco b);
int bancoInsereCirculo(Banco b, int id, double x, double y, double r, const char* corb, const char* corp);
int bancoInsereRetangulo(Banco b, int id, double x, double y, double w, double h, const char* corb, const char* corp);
int bancoInsereLinha(Banco b, int id, double x1, double y1, double x2, double y2, const char* cor);
int bancoInsereTexto(Banco b, int id, double x, double y, char ancora, const char* corb, const char* corp, const char* txt);
int bancoQuantidade(Banco b);
Forma bancoGet(Banco b, int i);
void bancoRemovePrimeiros(Banco b, int n);
void bancoInsereNoChao(Banco b, Forma f);
int formaTipo(Forma f);
int formaId(Forma f);
double formaX(Forma f);
double formaY(Forma f);
double formaW(Forma f);
double formaH(Forma f);
double formaR(Forma f);
double formaX2(Forma f);
double formaY2(Forma f);
const char* formaCorB(Forma f);
const char* formaCorP(Forma f);
const char* formaTxt(Forma f);
char formaAnc(Forma f);
Forma formaClona(Forma f, int novoIdTrocaCores);
void formaSetPos(Forma f, double x, double y);
void formaSetCorB(Forma f, const char* c);
void formaSetCorP(Forma f, const char* c);
double formaArea(Forma f);
Forma formaDup(Forma f);
#endif
