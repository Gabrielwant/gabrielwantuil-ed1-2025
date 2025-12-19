#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include "pilha.h"
#include "forma.h"
#include "disparador.h"

// Estrutura para armazenar posições de formas esmagadas
typedef struct
{
  double x;
  double y;
} PosicaoEsmagada;

// Variáveis globais do sistema
static Fila chao = NULL;
static Fila arena = NULL;
static Disparador disparadores[100];
static Carregador carregadores[100];
static int num_disparadores = 0;
static int num_carregadores = 0;
static int maior_id = 0;

// Estatísticas
static double pontuacao_total = 0.0;
static int num_instrucoes = 0;
static int num_disparos = 0;
static int num_esmagadas = 0;
static int num_clonadas = 0;

// Array para armazenar posições de formas esmagadas
static PosicaoEsmagada posicoes_esmagadas[1000];
static int num_posicoes_esmagadas = 0;

// Estilo de texto atual
static char font_family[50] = "sans-serif";
static char font_weight[20] = "normal";
static int font_size = 12;

// Arquivos de saída
static FILE *txt_out = NULL;
static FILE *svg_out = NULL;

void init_sistema()
{
  chao = create_fila();
  arena = create_fila();
  num_posicoes_esmagadas = 0;
}

void processar_comando_geo(char *linha)
{
  char cmd;
  sscanf(linha, " %c", &cmd);

  switch (cmd)
  {
  case 'c':
  { // círculo
    int id;
    double x, y, r;
    char corb[50], corp[50];
    sscanf(linha, " c %d %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp);

    Forma f = create_circulo(id, x, y, r, corb, corp);
    enqueue(chao, f);
    if (id > maior_id)
      maior_id = id;
    break;
  }
  case 'r':
  { // retângulo
    int id;
    double x, y, w, h;
    char corb[50], corp[50];
    sscanf(linha, " r %d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp);

    Forma f = create_retangulo(id, x, y, w, h, corb, corp);
    enqueue(chao, f);
    if (id > maior_id)
      maior_id = id;
    break;
  }
  case 'l':
  { // linha
    int id;
    double x1, y1, x2, y2;
    char cor[50];
    sscanf(linha, " l %d %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, cor);

    Forma f = create_linha(id, x1, y1, x2, y2, cor);
    enqueue(chao, f);
    if (id > maior_id)
      maior_id = id;
    break;
  }
  case 't':
  { // texto
    if (linha[1] == 's')
    { // comando ts
      char ff[50], fw[20];
      int fs;
      sscanf(linha, " ts %s %s %d", ff, fw, &fs);

      strcpy(font_family, ff);
      strcpy(font_weight, fw);
      font_size = fs;
    }
    else
    { // comando t
      int id;
      double x, y;
      char corb[50], corp[50], ancora;
      char *texto_ptr = strchr(linha, ' ');

      // Pular espaços e ler parâmetros
      int parsed = sscanf(linha, " t %d %lf %lf %s %s %c", &id, &x, &y, corb, corp, &ancora);

      // Encontrar início do texto (último parâmetro)
      char *p = linha;
      int spaces = 0;
      while (*p && spaces < 7)
      {
        if (*p == ' ')
          spaces++;
        p++;
      }
      while (*p == ' ')
        p++;

      char texto[500];
      strcpy(texto, p);
      // Remover quebra de linha
      texto[strcspn(texto, "\n")] = 0;

      Forma f = create_texto(id, x, y, corb, corp, ancora, texto);
      enqueue(chao, f);
      if (id > maior_id)
        maior_id = id;
    }
    break;
  }
  }
}

void processar_pd(char *linha)
{
  int id;
  double x, y;
  sscanf(linha, " pd %d %lf %lf", &id, &x, &y);

  disparadores[id] = create_disparador(id, x, y);
  num_instrucoes++;
}

void processar_lc(char *linha)
{
  int id, n;
  sscanf(linha, " lc %d %d", &id, &n);

  carregadores[id] = create_carregador(id);

  if (txt_out)
  {
    fprintf(txt_out, "Carregador %d:\n", id);
  }

  // Retirar n formas do chão e colocar no carregador
  for (int i = 0; i < n && !is_empty_fila(chao); i++)
  {
    Forma f = (Forma)dequeue(chao);
    add_forma_carregador(carregadores[id], f);

    if (txt_out)
    {
      fprintf(txt_out, "  ");
      escreve_forma_txt(f, txt_out);
    }
  }

  num_instrucoes++;
}

void processar_atch(char *linha)
{
  int id_disp, id_esq, id_dir;
  sscanf(linha, " atch %d %d %d", &id_disp, &id_esq, &id_dir);

  attach_carregadores(disparadores[id_disp],
                      carregadores[id_esq],
                      carregadores[id_dir]);

  num_instrucoes++;
}

void processar_shft(char *linha)
{
  int id_disp, n;
  char lado;
  sscanf(linha, " shft %d %c %d", &id_disp, &lado, &n);

  for (int i = 0; i < n; i++)
  {
    Forma f = shift_disparador(disparadores[id_disp], lado);

    if (txt_out && i == n - 1 && f != NULL)
    {
      fprintf(txt_out, "Forma em posição de disparo (disparador %d):\n", id_disp);
      fprintf(txt_out, "  ");
      escreve_forma_txt(f, txt_out);
    }
  }

  num_instrucoes++;
}

void processar_dsp(char *linha)
{
  int id_disp;
  double dx, dy;
  char vis = ' ';
  sscanf(linha, " dsp %d %lf %lf %c", &id_disp, &dx, &dy, &vis);

  Forma f = fire_disparador(disparadores[id_disp]);

  if (f != NULL)
  {
    double x_disp = get_x_disparador(disparadores[id_disp]);
    double y_disp = get_y_disparador(disparadores[id_disp]);

    double x_final = x_disp + dx;
    double y_final = y_disp + dy;

    move_forma(f, x_final, y_final);
    enqueue(arena, f);

    if (txt_out)
    {
      fprintf(txt_out, "Disparo (disparador %d):\n", id_disp);
      fprintf(txt_out, "  ");
      escreve_forma_txt(f, txt_out);
      fprintf(txt_out, "  Posição final: (%.2f, %.2f)\n", x_final, y_final);
    }

    num_disparos++;
  }

  num_instrucoes++;
}

void processar_rjd(char *linha)
{
  int id_disp;
  double dx, dy, ix, iy;
  char lado;
  sscanf(linha, " rjd %d %c %lf %lf %lf %lf", &id_disp, &lado, &dx, &dy, &ix, &iy);

  int i = 0;
  while (1)
  {
    // Shift
    Forma f = shift_disparador(disparadores[id_disp], lado);
    if (f == NULL)
      break;

    // Disparo
    f = fire_disparador(disparadores[id_disp]);
    if (f == NULL)
      break;

    double x_disp = get_x_disparador(disparadores[id_disp]);
    double y_disp = get_y_disparador(disparadores[id_disp]);

    double x_final = x_disp + dx + i * ix;
    double y_final = y_disp + dy + i * iy;

    move_forma(f, x_final, y_final);
    enqueue(arena, f);

    if (txt_out)
    {
      fprintf(txt_out, "Rajada disparo %d:\n", i);
      fprintf(txt_out, "  ");
      escreve_forma_txt(f, txt_out);
      fprintf(txt_out, "  Posição: (%.2f, %.2f)\n", x_final, y_final);
    }

    num_disparos++;
    i++;
  }

  num_instrucoes++;
}

void processar_calc()
{
  if (txt_out)
  {
    fprintf(txt_out, "\n=== PROCESSAMENTO DA ARENA ===\n");
  }

  double pontos_round = 0.0;

  Fila nova_arena = create_fila();

  while (!is_empty_fila(arena))
  {
    Forma f1 = (Forma)dequeue(arena);

    if (is_empty_fila(arena))
    {
      enqueue(nova_arena, f1);
      break;
    }

    Forma f2 = (Forma)dequeue(arena);

    double area1 = get_area_forma(f1);
    double area2 = get_area_forma(f2);

    int sobrepoe = formas_sobrepoem(f1, f2);

    if (txt_out)
    {
      fprintf(txt_out, "\nComparando forma %d (área=%.2f) com forma %d (área=%.2f)\n",
              get_id_forma(f1), area1, get_id_forma(f2), area2);
      fprintf(txt_out, "  Sobreposição: %s\n", sobrepoe ? "SIM" : "NÃO");
    }

    if (sobrepoe)
    {
      if (area1 < area2)
      {
        // f1 é esmagada - REGISTRAR POSIÇÃO
        double x_esmagada = get_x_forma(f1);
        double y_esmagada = get_y_forma(f1);

        if (num_posicoes_esmagadas < 1000)
        {
          posicoes_esmagadas[num_posicoes_esmagadas].x = x_esmagada;
          posicoes_esmagadas[num_posicoes_esmagadas].y = y_esmagada;
          num_posicoes_esmagadas++;
        }

        if (txt_out)
        {
          fprintf(txt_out, "  Forma %d ESMAGADA (área menor) na posição (%.2f, %.2f)\n",
                  get_id_forma(f1), x_esmagada, y_esmagada);
        }
        pontos_round += area1;
        pontuacao_total += area1;
        num_esmagadas++;

        destroy_forma(f1);
        enqueue(nova_arena, f2);
      }
      else
      {
        // f1 muda cor de borda de f2
        char *cor_preench_f1 = get_cor_preenchimento_forma(f1);
        set_cor_borda_forma(f2, cor_preench_f1);

        if (txt_out)
        {
          fprintf(txt_out, "  Forma %d muda cor de borda de forma %d\n",
                  get_id_forma(f1), get_id_forma(f2));
        }

        // Ambos voltam para arena
        enqueue(nova_arena, f1);
        enqueue(nova_arena, f2);

        // Clonar f1 com cores invertidas
        maior_id++;
        Forma clone = clone_forma(f1, maior_id);
        enqueue(nova_arena, clone);
        num_clonadas++;

        if (txt_out)
        {
          fprintf(txt_out, "  Forma %d clonada como forma %d\n",
                  get_id_forma(f1), maior_id);
        }
      }
    }
    else
    {
      // Sem sobreposição
      enqueue(nova_arena, f1);
      enqueue(nova_arena, f2);
    }
  }

  // Todas as formas da arena voltam para o chão
  while (!is_empty_fila(nova_arena))
  {
    Forma f = (Forma)dequeue(nova_arena);
    enqueue(chao, f);
  }

  destroy_fila(nova_arena);

  if (txt_out)
  {
    fprintf(txt_out, "\nPontuação deste round: %.2f\n", pontos_round);
    fprintf(txt_out, "Pontuação total acumulada: %.2f\n", pontuacao_total);
  }

  num_instrucoes++;
}

void gerar_svg(char *filename)
{
  FILE *svg = fopen(filename, "w");
  if (!svg)
    return;

  fprintf(svg, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
  fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1000\" height=\"1000\">\n");

  // Desenhar todas as formas do chão
  Posic p = get_first_fila(chao);
  while (p != NULL)
  {
    Forma f = (Forma)get_data_fila(chao, p);
    escreve_forma_svg(f, svg);
    p = get_next_fila(chao, p);
  }

  // ADICIONAR ASTERISCOS VERMELHOS NAS POSIÇÕES DAS FORMAS ESMAGADAS
  for (int i = 0; i < num_posicoes_esmagadas; i++)
  {
    double x = posicoes_esmagadas[i].x;
    double y = posicoes_esmagadas[i].y;

    // Desenhar asterisco como texto SVG
    fprintf(svg, "<text x=\"%.2f\" y=\"%.2f\" font-size=\"30\" fill=\"red\" "
                 "text-anchor=\"middle\" dominant-baseline=\"middle\" "
                 "font-weight=\"bold\">*</text>\n",
            x, y);
  }

  fprintf(svg, "</svg>\n");
  fclose(svg);
}

int main(int argc, char **argv)
{
  char *dir_entrada = NULL;
  char *dir_saida = NULL;
  char *arq_geo = NULL;
  char *arq_qry = NULL;
  char *sufixo = NULL;

  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-e") == 0 && i + 1 < argc)
      dir_entrada = argv[++i];
    else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
      arq_geo = argv[++i];
    else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
      dir_saida = argv[++i];
    else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc)
      arq_qry = argv[++i];
    else
      sufixo = argv[i];
  }

  if (!arq_geo || !dir_saida)
  {
    fprintf(stderr, "Uso: %s -e <dir> -f <geo> -o <saida> [-q <qry>] [sufixo]\n", argv[0]);
    return 1;
  }

  if (!dir_entrada)
    dir_entrada = ".";

  init_sistema();

  char caminho_geo[512];
  snprintf(caminho_geo, sizeof(caminho_geo), "%s/%s", dir_entrada, arq_geo);

  FILE *geo = fopen(caminho_geo, "r");
  if (!geo)
  {
    fprintf(stderr, "Erro ao abrir %s\n", caminho_geo);
    return 1;
  }

  char linha[1000];
  while (fgets(linha, sizeof(linha), geo))
  {
    if (linha[0] == '\n' || linha[0] == '#')
      continue;
    processar_comando_geo(linha);
  }
  fclose(geo);

  char nome_geo[256];
  strcpy(nome_geo, arq_geo);
  char *p = strrchr(nome_geo, '.');
  if (p)
    *p = '\0';

  char svg_geo[512];
  snprintf(svg_geo, sizeof(svg_geo), "%s/%s.svg", dir_saida, nome_geo);
  gerar_svg(svg_geo);

  if (arq_qry)
  {
    char caminho_qry[512];
    snprintf(caminho_qry, sizeof(caminho_qry), "%s/%s", dir_entrada, arq_qry);

    FILE *qry = fopen(caminho_qry, "r");
    if (!qry)
    {
      fprintf(stderr, "Erro ao abrir %s\n", caminho_qry);
      return 1;
    }

    char nome_qry[256];
    strcpy(nome_qry, arq_qry);
    p = strrchr(nome_qry, '.');
    if (p)
      *p = '\0';

    char txt_normal[512];
    snprintf(txt_normal, sizeof(txt_normal),
             "%s/%s-%s.txt", dir_saida, nome_geo, nome_qry);
    txt_out = fopen(txt_normal, "w");

    while (fgets(linha, sizeof(linha), qry))
    {
      if (linha[0] == '\n' || linha[0] == '#')
        continue;

      char cmd[16];
      sscanf(linha, " %s", cmd);

      if (!strcmp(cmd, "pd"))
        processar_pd(linha);
      else if (!strcmp(cmd, "lc"))
        processar_lc(linha);
      else if (!strcmp(cmd, "atch"))
        processar_atch(linha);
      else if (!strcmp(cmd, "shft"))
        processar_shft(linha);
      else if (!strcmp(cmd, "dsp"))
        processar_dsp(linha);
      else if (!strcmp(cmd, "rjd"))
        processar_rjd(linha);
      else if (!strcmp(cmd, "calc"))
        processar_calc();
    }

    fclose(qry);

    if (txt_out)
    {
      fprintf(txt_out, "\n=== ESTATÍSTICAS FINAIS ===\n");
      fprintf(txt_out, "Pontuação final: %.2f\n", pontuacao_total);
      fprintf(txt_out, "Número total de instruções: %d\n", num_instrucoes);
      fprintf(txt_out, "Número total de disparos: %d\n", num_disparos);
      fprintf(txt_out, "Número total de formas esmagadas: %d\n", num_esmagadas);
      fprintf(txt_out, "Número total de formas clonadas: %d\n", num_clonadas);
      fclose(txt_out);
    }

    char svg_final[512];
    snprintf(svg_final, sizeof(svg_final),
             "%s/%s-%s.svg", dir_saida, nome_geo, nome_qry);
    gerar_svg(svg_final);

    if (sufixo)
    {
      char txt_suf[512];
      snprintf(txt_suf, sizeof(txt_suf),
               "%s/%s-%s-%s.txt", dir_saida, nome_geo, nome_qry, sufixo);
      txt_out = fopen(txt_suf, "w");

      if (txt_out)
      {
        fprintf(txt_out, "\n=== ESTATÍSTICAS FINAIS ===\n");
        fprintf(txt_out, "Pontuação final: %.2f\n", pontuacao_total);
        fprintf(txt_out, "Número total de instruções: %d\n", num_instrucoes);
        fprintf(txt_out, "Número total de disparos: %d\n", num_disparos);
        fprintf(txt_out, "Número total de formas esmagadas: %d\n", num_esmagadas);
        fprintf(txt_out, "Número total de formas clonadas: %d\n", num_clonadas);
        fclose(txt_out);
      }

      char svg_suf[512];
      snprintf(svg_suf, sizeof(svg_suf),
               "%s/%s-%s-%s.svg", dir_saida, nome_geo, nome_qry, sufixo);
      gerar_svg(svg_suf);
    }
  }

  return 0;
}
