
#ifndef JOGO_H
#define JOGO_H
#include "formas.h"
#include "banco.h"
typedef struct pilha* Pilha;
typedef struct fila* Fila;
typedef struct carreg* Carreg;
typedef struct disp* Disp;
typedef struct arena* Arena;
Pilha criaPilha(void);
void empilha(Pilha p, Forma f);
Forma desempilha(Pilha p);
int pilhaVazia(Pilha p);
void destroiPilha(Pilha p);
Fila criaFila(void);
void enfileira(Fila f, Forma g);
Forma desenfileira(Fila f);
int filaVazia(Fila f);
void destroiFila(Fila f);
Carreg criaCarreg(int id);
void destroiCarreg(Carreg c);
void carregPush(Carreg c, Forma f);
Forma carregPop(Carreg c);
int carregVazio(Carreg c);
Disp criaDisp(int id);
void destroiDisp(Disp d);
void dispPos(Disp d, double x, double y);
void dispLiga(Disp d, Carreg e, Carreg dir);
Forma dispShift(Disp d, char lado);
Forma dispFire(Disp d, double dx, double dy, char modo, double* outx, double* outy);
Arena criaArena(void);
void destroiArena(Arena a);
void arenaLanca(Arena a, Forma f, double x, double y);
int arenaCount(Arena a);
Forma arenaGet(Arena a, int i);
double arenaGetX(Arena a, int i);
double arenaGetY(Arena a, int i);
void arenaLimpa(Arena a);
typedef struct jogo* Jogo;
Jogo criaJogo(BancoGlobal bg);
void destroiJogo(Jogo j);
Carreg jogoGetCarreg(Jogo j, int id, int cria);
Disp jogoGetDisp(Jogo j, int id, int cria);
void jogoCarregaDoChao(Jogo j, int cid, int n);
void jogoEmpilhaChao(Jogo j, Forma f);
int jogoChaoQtd(Jogo j);
void jogoArenaDispara(Jogo j, Disp d, double dx, double dy, char modo);
double jogoCalc(Jogo j, double** ax, double** ay, int* nsm, double* pont, int* totIns, int* totDsp, int* totEsm, int* totClo);
Banco jogoGetChao(Jogo j);
#endif
