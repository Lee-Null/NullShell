CC = gcc

shell : interpret.o
	$(CC) -o shell shell.c interpret.o

interpret.o :
	$(CC) -c -o interpret.o interpret.c

clean:
	rm *.o shell