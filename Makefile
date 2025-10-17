CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -fstack-protector-all -Iinclude
LDFLAGS = -lm
SRCDIR = src
OBJ = $(SRCDIR)/main.o $(SRCDIR)/pilha.o $(SRCDIR)/fila.o $(SRCDIR)/formas.o $(SRCDIR)/disparador.o $(SRCDIR)/qry.o

all: ted

ted: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q $(SRCDIR)\*.o ted.exe 2>nul || rm -f $(SRCDIR)/*.o ted

.PHONY: all clean

testepilha: src/pilha.o src/testepilha.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

testefila: src/fila.o src/testefila.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
