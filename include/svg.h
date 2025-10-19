
#ifndef SVG_H
#define SVG_H
#include "formas.h"
void escreveSvgGeo(const char* saidaDir, const char* base, Banco b, const char* fontfam, const char* fweight, double fsize);
void escreveSvgQryFinal(const char* saidaDir, const char* baseGeo, const char* baseQry, Banco b, double* esmagx, double* esmagy, int nesmags);
#endif
