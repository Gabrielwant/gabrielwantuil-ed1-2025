# Nome do executável final
PROJ_NAME=ted

# Nome do aluno
NOME_ALUNO=Gabriel Wantuil

# Compilador
CC=gcc

# Flags de compilação
# IMPORTANTE: Removido -fstack-protector-all para compatibilidade Windows
CFLAGS=-std=c99 -Wall -Wextra -O0 -g

# Bibliotecas a serem linkadas
LIBS=-lm

# Lista de todos os arquivos fonte .c
SOURCES=$(wildcard *.c)

# Cria a lista de arquivos objeto .o
OBJETOS=$(SOURCES:.c=.o)

# --- REGRAS DE COMPILAÇÃO ---

# Regra padrão
all: $(PROJ_NAME)

# Linkar todos os objetos
$(PROJ_NAME): $(OBJETOS)
	$(CC) -o $(PROJ_NAME) $(OBJETOS) $(LIBS)
	@echo Compilacao concluida: $(PROJ_NAME)

# Compilar .c em .o
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# Limpar arquivos gerados
clean:
	rm -f *.o $(PROJ_NAME) $(PROJ_NAME).exe

# Define que estas não são arquivos
.PHONY: all clean