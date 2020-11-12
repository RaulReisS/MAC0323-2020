#Makefile para o EP2
LIBDIR = /usr/local/lib 
FLAGS = -Wall -std=c99 -pedantic -O2

all: EP1 tidyup

EP1: main.o node.o filaCPU.o filaEspera.o
	gcc -o EP2 main.o node.o filaCPU.o filaEspera.o

main.o: main.c node.h filaCPU.h filaEspera.h
	gcc $(FLAGS) main.c -c

node.o: node.c node.h
	gcc $(FLAGS) node.c -c

filaEspera.o: filaEspera.c filaEspera.h node.h
	gcc $(FLAGS) filaEspera.c -c

filaCPU.o: filaCPU.c filaCPU.h node.h
	gcc $(FLAGS) filaCPU.c -c

tidyup:
	rm -rf *.o *~

clean:
	rm -rf *.o *~ EP2