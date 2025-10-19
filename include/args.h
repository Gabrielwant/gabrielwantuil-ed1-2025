
#ifndef ARGS_H
#define ARGS_H
typedef struct args* Args;
Args criaArgs(void);
void destroiArgs(Args a);
int parseArgs(Args a, int argc, char** argv);
const char* getEntradaDir(Args a);
const char* getGeo(Args a);
const char* getQry(Args a);
const char* getSaidaDir(Args a);
#endif
