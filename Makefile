CC = gcc

all : shell

shell : interpret.o util.o shell.o 
	$(CC) -o shell shell.o interpret.o util.o

interpret.o : interpret.c
	$(CC) -c -o interpret.o interpret.c

util.o : util.c
	$(CC) -c -o util.o util.c

shell.o : shell.c
	$(CC) -c -o shell.o shell.c

clean:
	rm *.o shell