
#ifndef BANCO_H
#define BANCO_H
#include "formas.h"
typedef struct bancoGlobal* BancoGlobal;
BancoGlobal criaBancoGlobal(void);
void destroiBancoGlobal(BancoGlobal bg);
Banco getChao(BancoGlobal bg);
void setEstiloTexto(BancoGlobal bg, const char* fam, const char* peso, double tam);
void getEstiloTexto(BancoGlobal bg, char* fam, char* peso, double* tam);
int bancoMaxId(BancoGlobal bg);
void bancoFixMaxId(BancoGlobal bg, int id);
#endif
