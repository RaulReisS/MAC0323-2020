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

  node.c
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/
#include "node.h"
#include <stdlib.h>
#include <stdio.h>

Link newNode(unsigned int id, unsigned int priori, int cpuTime, int lines, Link next, Link prev) {
	Link node = malloc(sizeof(*node));
	node->id = id;
	node->priori = priori;
	node->timeNeed = node->cpuTime = cpuTime;
	node->linesNeed = node->lines = lines;
	node->time = 0;
	node->timeWait = node->timeCPU = node->timePrinter = 0;
	node->next = next;
	node->prev = prev;

	return node;
}


bool temLinhas(Link node) {
	if (node->lines <= 0)
		return false;
	return true;
}

unsigned int prioriNode(Link node) {
	return node->priori;
}

Link imprimeLinhas(Link node) {
	if (node != NULL) {
		node->lines = node->lines - 10;
		if (node->lines <= 0)
			return node;
	}
	return NULL;
}

void printNode(Link node) {
	if (node == NULL) 
		printf("NULL\n");
	else 
		printf("Id: %d\nCpuTime: %d\nLines: %d\n", node->id, node->cpuTime, node->lines);
}

void freeNode(Link node) {
	free(node);
}
