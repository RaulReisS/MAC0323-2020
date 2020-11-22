#Makefile para o EP3
LIBDIR = /usr/local/lib 
FLAGS = -Wall -std=c99 -pedantic -O2

all: ep3 tidyup

ep3: main.o util.o bst.o rubronegra.o list.o hashencadeado.o
	gcc -o ep3 main.o util.o bst.o rubronegra.o list.o hashencadeado.o

main.o: main.c bst.h rubronegra.h hashencadeado.h
	gcc $(FLAGS) main.c -c

bst.o: bst.c bst.h util.h
	gcc $(FLAGS) bst.c -c

rubronegra.o: rubronegra.c rubronegra.h util.h
	gcc $(FLAGS) rubronegra.c -c

hashencadeado.o: hashencadeado.c hashencadeado.h util.h list.h
	gcc $(FLAGS) hashencadeado.c -c

list.o: list.c list.h util.h
	gcc $(FLAGS) list.c -c

util.o: util.c util.h
	gcc $(FLAGS) util.c -c

tidyup:
	rm -rf *.o *~

clean:
	rm -rf *.o *~ ep3