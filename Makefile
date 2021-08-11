CFLAGS = -Wall --std=gnu99
CC = gcc
arg1 = $(shell $2)

bdt: bdt.c 
	$(CC) -o bdt $(CFLAGS) bdt.c 

clean:
	rm -f bdt *.o

run:
	./bdt $(arg1) file2.txt
