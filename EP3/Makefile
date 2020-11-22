#Makefile para o EP3
LIBDIR = /usr/local/lib 
FLAGS = -Wall -std=c99 -pedantic -O2

all: ep3 tidyup

ep3: main.o util.o bst.o rubronegra.o list.o hashencadeado.o hashlinear.o trie.o
	gcc -o ep3 main.o util.o bst.o rubronegra.o list.o hashencadeado.o hashlinear.o trie.o

main.o: main.c bst.h rubronegra.h hashencadeado.h hashlinear.h trie.h
	gcc $(FLAGS) main.c -c

bst.o: bst.c bst.h util.h
	gcc $(FLAGS) bst.c -c

rubronegra.o: rubronegra.c rubronegra.h util.h
	gcc $(FLAGS) rubronegra.c -c

hashencadeado.o: hashencadeado.c hashencadeado.h util.h list.h
	gcc $(FLAGS) hashencadeado.c -c

list.o: list.c list.h util.h
	gcc $(FLAGS) list.c -c

hashlinear.o: hashlinear.c hashlinear.h util.h
	gcc $(FLAGS) hashlinear.c -c

trie.o: trie.c trie.h util.h
	gcc $(FLAGS) trie.c -c

util.o: util.c util.h
	gcc $(FLAGS) util.c -c

tidyup:
	rm -rf *.o *~

clean:
	rm -rf *.o *~ ep3