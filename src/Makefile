CC=gcc
CFLAGS=-g -Wall
DEPS = film.h
OBJ = factorisation.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

factorisation: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

projetcsd: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
