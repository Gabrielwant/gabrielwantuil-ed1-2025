
#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "banco.h"
#include "parser_geo.h"
#include "parser_qry.h"
#include "svg.h"

int main(int argc,char** argv)
{
    Args a=criaArgs();
    if(!parseArgs(a,argc,argv))
    {
        printf("Uso: ted -f arquivo.geo -o diretorio_saida [-e dir_entrada] [-q arquivo.qry]\n");
        destroiArgs(a);
        return 1;
    }
    BancoGlobal bg=criaBancoGlobal();
    if(!processaGeo(getEntradaDir(a),getGeo(a),bg))
    {
        printf("Falha ao ler .geo\n");
        destroiBancoGlobal(bg);
        destroiArgs(a);
        return 1;
    }
    char fam[32], peso[8]; double tam=12.0;
    getEstiloTexto(bg,fam,peso,&tam);
    escreveSvgGeo(getSaidaDir(a),getGeo(a),getChao(bg),fam,peso,tam);
    const char* qry=getQry(a);
    if(qry) processaQry(getEntradaDir(a),qry,bg,getSaidaDir(a),getGeo(a));
    destroiBancoGlobal(bg);
    destroiArgs(a);
    return 0;
}
