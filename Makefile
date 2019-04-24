CC = gcc

all : shell

shell : interpret.o shell.c
	$(CC) -o shell shell.c interpret.o

interpret.o : interpret.c interpret.h
	$(CC) -c -o interpret.o interpret.c

clean:
	rm *.o shell