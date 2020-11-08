/*    
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

  AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP, 
  DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA. 
  TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO-PROGRAMA (EP) FORAM 
  DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES DESSE EP
  E QUE PORTANTO NÃO CONSTITUEM PLÁGIO. DECLARO TAMBÉM QUE SOU RESPONSÁVEL
  POR TODAS AS CÓPIAS DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
  SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO SÃO PUNIDOS COM 
  REPROVAÇÃO DIRETA NA DISCIPLINA.

  Nome: Raul dos Reis Soares
  NUSP: 8535596

  filaEspera.c
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/
#include <stdio.h>
#include "filaEspera.h"
#include "node.h"
    /* Implementação das rotinas auxiliares */

// Essa função afunda um processo na estrutua de heap de acordo com a sua prioridade
static void sink(FilaEspera fila, int i) {
    int f = 2*i+1;
    Link aux = fila->heap[i];
    if (f+1 < fila->size && grater(fila->heap[f+1], fila->heap[f])) 
        f++;
    while (f < fila->size && grater(fila->heap[f], aux)) {
        fila->heap[i] = fila->heap[f];
        fila->heap[i]->index = i;
        i = f;
        f = 2*i+1;
        if (f+1 < fila->size && grater(fila->heap[f+1],fila->heap[f]))
            f++;
    }
    fila->heap[i] = aux;
    fila->heap[i]->index = i;
}

// Essa função sobe um processo na estrutua de heap de acordo com a sua prioridade
static void swim(FilaEspera fila, int i) {
    int p = (i-2)/2;
    Link aux = fila->heap[i];
    while (i > 0 && grater(aux, fila->heap[p])) {
        fila->heap[i] = fila->heap[p];
        fila->heap[i]->index = i;
        i = p;
        p = (i-1)/2;
    }
    fila->heap[i] = aux;
    fila->heap[i]->index = i;
}

// Essa função redimensiona o tamanho do vetor de heap de acordo com o número de processos nele
static void resize(FilaEspera fila) {
    if (fila->size == fila->max) {
        fila->max = fila->max * 2;
        Link *aux = malloc((fila->max)*sizeof(Link));

        for (unsigned int i = 0; i < fila->size; i++) {
            aux[i] = fila->heap[i];
        }

        free(fila->heap);
        fila->heap = aux;
    }
    else if (fila->size < fila->max/4) {
        fila->max = (unsigned int) fila->max/4;
        Link *aux = malloc((fila->max)*sizeof(Link));

        for (unsigned int i = 0; i < fila->size; i++) {
            aux[i] = fila->heap[i];
        }

        free(fila->heap);
        fila->heap = aux;
    }
}

    /* Implementação das rotinas de interface */

FilaEspera criaFilaEspera() {
    FilaEspera fila = malloc(sizeof(*fila));
    Link head = newNode(0, 10, 0, 0, NULL, NULL);
    head->next = head;
    head->prev = head;
    fila->head = head;
    fila->max = 10;
    fila->heap = malloc((fila->max)*sizeof(Link));
    fila->size = 0;
    return fila;
}

void enfilaEspera(FilaEspera fila, Link node) {
    if (node != NULL) {
        // Manipulando fila circular
        Link head = fila->head;
        Link prev = fila->head->prev;

        node->next = head;
        node->prev = prev;
        prev->next = node;
        head->prev = node;
        node->time = TIME;

        // Manipulando heap
        fila->heap[fila->size] = node;
        node->index = fila->size;
        swim(fila, fila->size);
        fila->size += 1;
        resize(fila);
    }
}


Link desenfilaEspera(FilaEspera fila) {
    Link out = NULL;
    if (fila->size == 0)
        return out;
    else if (fila->prior == false) {
        // Subindo o processo a ser retirado no heap
        unsigned int aux = fila->head->next->priori;
        fila->head->next->priori = 10;
        swim(fila, fila->head->next->index);
        fila->head->next->priori = aux;
    }
    // Removendo do heap
    out = fila->heap[0];
    fila->size -= 1;
    fila->heap[0] = fila->heap[fila->size];
    fila->heap[0]->index = 0;
    sink(fila, 0);

    // Removendo da fila circular
    Link next = out->next;
    Link prev = out->prev;
    prev->next = next;
    next->prev = prev;
    out->next = NULL;
    out->prev = NULL;

    resize(fila);

    if (fila->prior == true)
        fila->prior = false;
    else
        fila->prior = true;

    return out;
}

bool vaziaEspera(FilaEspera fila) {
    if (fila->size == 0)
        return true;
    return false;
}

int tamEspera(FilaEspera fila) {
    return fila->size;
}

unsigned int* contagemEspera(FilaEspera fila) {
    unsigned int *cont = malloc(10*sizeof(unsigned int));
    Link node = fila->head->next;

    for (unsigned int i = 0; i < 10; i++)
        cont[i] = 0;

    while(node != fila->head) {
        cont[node->priori] += 1;

        node = node->next;
    }

    return cont;
}

void timeAddEspera(FilaEspera fila) {
    Link node = fila->head->next;

    while (node != fila->head) {
        node->timeWait = node->timeWait + 1;
        node = node->next;
    }
}

void printFilaEspera(FilaEspera fila)  {
    Link node = fila->head->next;
    while (node != fila->head) {
        printNode(node);
        node = node->next;
    }
}

void liberaFilaEspera(FilaEspera fila) {
    Link node = fila->head->next;
    free(fila->heap);
    fila->heap = NULL;

    while(node != fila->head) {
        Link out = node;
        node = out->next;
        free(out);
    }
    free(fila->head);
    fila->head = NULL;
    free(fila);
    fila = NULL;
}