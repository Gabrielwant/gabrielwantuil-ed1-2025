PROJ_NAME=ted

CC=gcc
CFLAGS=-std=c99 -fstack-protector-all -Wall -Wextra -I../include
LDFLAGS=
OBJ=main.o args.o util.o formas.o svg.o banco.o parser_geo.o parser_qry.o jogo.o geom.o saida.o pilha.o fila.o disp.o

all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(PROJ_NAME) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(PROJ_NAME)
	./$(PROJ_NAME) -e ../tests -f exemplo.geo -o ../tests/out -q exemplo.qry

clean:
	- rm -f *.o $(PROJ_NAME)

.PHONY: all run clean