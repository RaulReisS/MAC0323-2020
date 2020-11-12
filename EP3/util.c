#include <stdio.h>
#include <stdlib.h>

void *mallocSafe(size_t nbytes) {
  void *p = malloc(nbytes);
  
  if (p == NULL) {
    printf("Erro: alocação de memória falhou no módulo util.");
    exit(0);
  }
  return p;
}