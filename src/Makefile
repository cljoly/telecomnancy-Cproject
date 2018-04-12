CC=gcc
CFLAGS=-g -Wall
DEPS = movie.h stringlist.h movies_list_loader.h
OBJ = factorisation.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

factorisation: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

testparser: movie.o stringlist.o movies_list_loader.o testparser.o
	gcc -o $@ $^ $(CFLAGS) -lwjelement -lwjreader -lwjwriter

projetcsd: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
