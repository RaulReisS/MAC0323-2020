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

  filaCPU.c
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/
#include "filaCPU.h"
#include <stdio.h>

Fila criaFila() {
	Fila fila = malloc(sizeof(*fila));
	Link head = newNode(0, 10, 0, 0, NULL, NULL);
	head->next = head;
	head->prev = head;
	fila->head = head;
	head->cpuTime = 0;
	fila->size = 0;
	return fila;
}

void enfila(Fila fila, Link node) {
	if (node != NULL) {
		Link head = fila->head;
		Link prev = fila->head->prev;

		node->next = head;
		node->prev = prev;
		prev->next = node;
		head->prev = node;
		node->time = TIME;

		fila->size = fila->size + 1;
	}
}

Link desenfila(Fila fila) {
	if (fila->size == 0)
		return NULL;
	Link head = fila->head;
	Link out = head->next;
	Link next = out->next;

	head->next = next;
	next->prev = head;
	out->next = out->prev = NULL;
	fila->size = fila->size -1;
	return out; 
}

bool vazia(Fila fila) {
	if (fila->size == 0)
		return true;
	return false;
}

bool cheia(Fila fila) {
	if (fila->size < MAX)
		return false;
	else 
		return true;
}

int tam(Fila fila) {
	return fila->size;
}

void anda(Fila fila) {
	if (fila->size > 0) {
		Link node = desenfila(fila);
		enfila(fila, node);
	}
}

void timeAdd(Fila fila, char nome) {
	Link node = fila->head->next;

	while (node != fila->head) {
		if (nome == FWAIT)
			node->timeWait = node->timeWait + 1;
		else if (nome == FCPU)
			node->timeCPU = node->timeCPU + 1;
		else if (nome == FPRINT)
			node->timePrinter = node->timePrinter + 1;

		node = node->next;
	}
}

Link clockCPU(Fila fila) {
	if (fila->size == 0)
		return NULL;
	Link process = fila->head->next;

	process->cpuTime = process->cpuTime - 1;
	process->time = process->time - 1;

	if (process->cpuTime <= 0)
		return desenfila(fila);
	
	if (process->time <= 0)
		anda(fila);

	return NULL;
}

void printFila(Fila fila) {
	Link node = fila->head->next;
	while (node != fila->head) {
		printNode(node);
		node = node->next;
	}
}

void liberaFila(Fila fila) {
	Link node = fila->head->next;
	while (node != fila->head) {
		Link out = node;
		node = out->next;
		free(out);
	}
	free(fila->head);
	fila->head = NULL;
	free(fila);
	fila = NULL;
}