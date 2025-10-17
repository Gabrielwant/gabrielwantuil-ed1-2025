#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formas.h"
#include "qry.h"

int main(int argc, char *argv[])
{
    char arquivoGeo[100] = "";
    char arquivoQry[100] = "";
    char dirSaida[100] = "";

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
            strcpy(arquivoGeo, argv[++i]);
        else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc)
            strcpy(arquivoQry, argv[++i]);
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
            strcpy(dirSaida, argv[++i]);
    }

    if (strlen(arquivoGeo) == 0 || strlen(dirSaida) == 0)
    {
        printf("Uso: ted -f arquivo.geo [-q arquivo.qry] -o diretorio_saida\n");
        return 1;
    }

    FILE *geo = fopen(arquivoGeo, "r");
    if (!geo)
    {
        printf("Erro ao abrir %s\n", arquivoGeo);
        return 1;
    }

    char svgPath[200];
    sprintf(svgPath, "%s/base.svg", dirSaida);

    FILE *svg = fopen(svgPath, "w");
    if (!svg)
    {
        printf("Erro ao criar %s\n", svgPath);
        fclose(geo);
        return 1;
    }

    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");

    char tipo;
    int id;
    double x, y, w, h, r;
    char corb[30], corp[30];

    while (fscanf(geo, " %c", &tipo) == 1)
    {
        if (tipo == 'c')
        {
            if (fscanf(geo, "%d %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp) == 6)
            {
                Forma *f = criaCirculo(id, x, y, r, corb, corp);
                escreveCirculoSVG(svg, f);
                liberaForma(f);
            }
        }
        else if (tipo == 'r')
        {
            if (fscanf(geo, "%d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp) == 7)
            {
                Forma *f = criaRetangulo(id, x, y, w, h, corb, corp);
                escreveRetanguloSVG(svg, f);
                liberaForma(f);
            }
        }
    }

    fprintf(svg, "</svg>\n");

    fclose(geo);
    fclose(svg);

    printf("Arquivo SVG gerado em: %s\n", svgPath);

    if (strlen(arquivoQry) > 0)
        processaQry(arquivoQry);

    return 0;
}
