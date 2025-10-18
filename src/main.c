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
    char fontFamily[16] = "sans";
    char fontWeight[8] = "n";
    double fontSize = 12.0;

    while (fscanf(geo, " %c", &tipo) == 1)
    {
        if (tipo == 'c')
        {
            int id;
            double x, y, r;
            char corb[30], corp[30];
            fscanf(geo, "%d %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp);
            Forma *f = criaCirculo(id, x, y, r, corb, corp);
            escreveCirculoSVG(svg, f);
            liberaForma(f);
        }
        else if (tipo == 'r')
        {
            int id;
            double x, y, w, h;
            char corb[30], corp[30];
            fscanf(geo, "%d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp);
            Forma *f = criaRetangulo(id, x, y, w, h, corb, corp);
            escreveRetanguloSVG(svg, f);
            liberaForma(f);
        }
        else if (tipo == 'l')
        {
            int id;
            double x1, y1, x2, y2;
            char cor[30];
            fscanf(geo, "%d %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, cor);
            Forma *f = criaLinha(id, x1, y1, x2, y2, cor);
            escreveLinhaSVG(svg, f);
            liberaForma(f);
        }
        else if (tipo == 't')
        {
            int id;
            double x, y;
            char corb[30], corp[30], a, texto[256];
            fscanf(geo, "%d %lf %lf %s %s %c", &id, &x, &y, corb, corp, &a);
            fgets(texto, sizeof(texto), geo);
            texto[strcspn(texto, "\r\n")] = 0;
            Forma *f = criaTexto(id, x, y, corb, corp, a, texto);
            escreveTextoSVG(svg, f, fontFamily, fontWeight, fontSize);
            liberaForma(f);
        }
        else if (tipo == 'ts')
        {
            char fam[16], weight[8];
            double size;
            fscanf(geo, "%s %s %lf", fam, weight, &size);
            strcpy(fontFamily, fam);
            strcpy(fontWeight, weight);
            fontSize = size;
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
