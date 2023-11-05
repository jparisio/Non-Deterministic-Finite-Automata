all: a1

a1: a1.o
	gcc -Wall -std=c99 -pedantic -o a1 a1.o


a1.c:
	gcc -c -Wall -std=c99 -pedantic a1.c

clean:
	rm -rfv *o a1
