
#include <stdio.h>
#include <stdlib.h>
#include "svg.h"
#include "util.h"
#include "formas.h"

static void escreveEstilo(FILE *f, const char *fam, const char *w, double sz)
{
    fprintf(f, "<style> text { font-family:%s; font-size: %.1fpx; font-weight:%s; }</style>\n", fam, sz, w);
}

static void escreveFormas(FILE *f, Banco b)
{
    for (int i = 0; i < bancoQuantidade(b); i++)
    {
        Forma g = bancoGet(b, i);
        int t = formaTipo(g);
        if (t == 1)
        {
            fprintf(f, "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"0.5\" />\n", formaX(g), formaY(g), formaR(g), formaCorB(g), formaCorP(g));
            fprintf(f, "<text x=\"%.2f\" y=\"%.2f\" fill=\"%s\">%d</text>\n", formaX(g), formaY(g), formaCorB(g), formaId(g));
        }
        else if (t == 2)
        {
            fprintf(f, "<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"0.5\" />\n", formaX(g), formaY(g), formaW(g), formaH(g), formaCorB(g), formaCorP(g));
            fprintf(f, "<text x=\"%.2f\" y=\"%.2f\" fill=\"%s\">%d</text>\n", formaX(g), formaY(g), formaCorB(g), formaId(g));
        }
        else if (t == 3)
        {
            fprintf(f, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\" />\n", formaX(g), formaY(g), formaX2(g), formaY2(g), formaCorB(g));
        }
        else if (t == 4)
        {
            fprintf(f, "<text x=\"%.2f\" y=\"%.2f\" fill=\"%s\">%s</text>\n", formaX(g), formaY(g), formaCorP(g), formaTxt(g));
        }
    }
}

void escreveSvgGeo(const char *saidaDir, const char *base, Banco b, const char *fam, const char *w, double sz)
{
    util_ensure_dir(saidaDir);
    char fname[1400];
    util_copy(fname, saidaDir, 1399);
    int a = util_strlen(fname);
    if (a > 0 && fname[a - 1] != '/')
    {
        fname[a] = '/';
        fname[a + 1] = 0;
    }
    util_join3(fname, fname, base, ".svg", 1399);
    FILE *f = fopen(fname, "w");
    if (!f)
        return;
    fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1200\" height=\"1200\">\n");
    escreveEstilo(f, fam, w, sz);
    escreveFormas(f, b);
    fprintf(f, "</svg>\n");
    fclose(f);
}

void escreveSvgQryFinal(const char *saidaDir, const char *baseGeo, const char *baseQry, Banco b, double *ex, double *ey, int ne)
{
    util_ensure_dir(saidaDir);
    char base[800];
    base[0] = 0;
    util_copy(base, baseGeo, 799);
    int n = util_strlen(base);
    int i = n - 1;
    while (i >= 0 && base[i] != '/')
        i--;
    const char *geo = (i >= 0) ? base + i + 1 : base;
    char outname[1024];
    util_copy(outname, saidaDir, 1023);
    int k = util_strlen(outname);
    if (k > 0 && outname[k - 1] != '/')
    {
        outname[k] = '/';
        outname[k + 1] = 0;
    }
    char mid[1024];
    util_copy(mid, geo, 1023);
    int m = util_strlen(mid);
    while (m > 0 && mid[m - 1] != '.')
        m--;
    mid[m - 1] = 0;
    char fin[1400];
    util_join3(fin, outname, mid, "-", 1399);
    util_join3(fin, fin, baseQry, ".svg", 1399);
    FILE *f = fopen(fin, "w");
    if (!f)
        return;
    fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1200\" height=\"1200\">\n");
    escreveEstilo(f, "sans", "n", 12.0);
    escreveFormas(f, b);
    for (int j = 0; j < ne; j++)
    {
        fprintf(f, "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"3.0\" fill=\"red\" />\n", ex[j], ey[j]);
    }
    fprintf(f, "</svg>\n");
    fclose(f);
}
