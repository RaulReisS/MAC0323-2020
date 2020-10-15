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

  node.h
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/
#ifndef _NODE
#define _NODE

#include <stdbool.h>
typedef struct Node* Link;

struct Node
{
	unsigned int id; // Id do processo
	unsigned int priori; // Prioridade do processo
	unsigned int timeNeed; // Tempo inicial de processamento necessário
	int cpuTime; // Tempo de processamento necessário restante
	unsigned int linesNeed; // Linhas a serem impressas 
	int lines; // Linhas restantes a serem impressas
	int time; // Tempo de uso da CPU desde que ficou no início da fila
	unsigned int timeWait; // Tempo de permanência na fila de espera
	unsigned int timeCPU; // Tempo de permanência na fila da CPU
	unsigned int timePrinter; // Tempo de permanência na fila de impressão
	Link next; // Apontador para o próximo item na fila
	Link prev; // Apontador para o item anterior na fila
};

// Essa função aloca a memória de um novo Node e retorna um apontador para a
// memória alocada com os parâmetros passados
Link newNode(unsigned int id, unsigned int priori, int cpuTime, int lines, Link next, Link prev);

// Informa se um Node tem linhas para imprimir (int lines)
bool temLinhas(Link node);

// Retorna a prioridade do processo representado por node
unsigned int prioriNode(Link node)

// Realiza a ação de "imprimir" as linhas de um processo na impressoa em que
// ele se encontra
Link imprimeLinhas(Link node);

// Essa função imprime as informações principais de um apontador para um node
// imprime "NULL" caso o node seja NULL
void printNode(Link node);

// Essa função libera a memória apontada pelo parâmetro
void freeNode(Link node);
#endif