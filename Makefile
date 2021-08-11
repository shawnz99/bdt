CFLAGS = -Wall --std=gnu99
CC = gcc

bdt: bdt.c 
	$(CC) -o bdt $(CFLAGS) bdt.c 

clean:
	rm -f bdt *.o

