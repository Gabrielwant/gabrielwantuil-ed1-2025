#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formas.h"

int main(int argc, char *argv[])
{
    char arquivoGeo[100] = "";
    char dirSaida[100] = "";

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
            strcpy(arquivoGeo, argv[++i]);
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
            strcpy(dirSaida, argv[++i]);
    }

    if (strlen(arquivoGeo) == 0 || strlen(dirSaida) == 0)
    {
        printf("Uso: ted -f arquivo.geo -o diretorio_saida\n");
        return 1;
    }

    FILE *geo = fopen(arquivoGeo, "r");
    if (!geo)
    {
        printf("Erro ao abrir %s\n", arquivoGeo);
        return 1;
    }

    printf("Lendo arquivo: %s\n", arquivoGeo);
    char tipo;
    int id;
    double x, y, w, h, r;
    char corb[30], corp[30];

    while (fscanf(geo, " %c", &tipo) == 1)
    {
        if (tipo == 'c')
        {
            fscanf(geo, "%d %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp);
            Forma *f = criaCirculo(id, x, y, r, corb, corp);
            imprimeForma(f);
            liberaForma(f);
        }
        else if (tipo == 'r')
        {
            fscanf(geo, "%d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp);
            Forma *f = criaRetangulo(id, x, y, w, h, corb, corp);
            imprimeForma(f);
            liberaForma(f);
        }
    }

    fclose(geo);
    return 0;
}
