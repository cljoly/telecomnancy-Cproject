CC=gcc
DEPS = movie.h stringlist.h movies_list_loader.h tools.h factorisation.h
CFLAGS=-g -Wall `gsl-config --cflags --libs`
OBJ = factorisation.o factorisation_test.o tools.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

factorisation_test: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

testparser: movie.o stringlist.o movies_list_loader.o testparser.o tools.o
	gcc -o $@ $^ $(CFLAGS) -lwjelement -lwjreader -lwjwriter

test_console_display: movie.o stringlist.o movies_list_loader.o test_console_display.o console_display.o tools.o
	gcc -o $@ $^ $(CFLAGS) -lwjelement -lwjreader -lwjwriter

test_prg_console: movie.o stringlist.o movies_list_loader.o console_display.o console_controler.o test_prg_console.o tools.o
	gcc -o $@ $^ $(CFLAGS) -lwjelement -lwjreader -lwjwriter

projetcsd: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
