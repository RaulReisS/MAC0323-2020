#Makefile para o EP1
LIBDIR = /usr/local/lib 
FLAGS = -Wall -std=c99 -pedantic -O2

all: EP1

EP1: main.o node.o filaCPU.o
	gcc -o EP1 main.o node.o filaCPU.o

main.o: main.c node.h filaCPU.h
	gcc $(FLAGS) main.c -c

node.o: node.c node.h
	gcc $(FLAGS) node.c -c

filaCPU.o: filaCPU.c filaCPU.h node.h
	gcc $(FLAGS) filaCPU.c -c

clean:
	rm -rf *.o *~ EP1