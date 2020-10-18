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

  filaEspera.h
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/
#ifndef _FILAESPERA
#define _FILAESPERA

#include <stdbool.h>
#include <stdlib.h>
#include "node.h"

#define TIME 20

struct FILAESPERA {
	Link head; // Apontador para o nó cabeça da fila ordenada por tempo de chegada 
  Link *heap; // Apontador para o vetor da fila de piroridade
	unsigned int size; // Tamanho da fila
  unsigned int max; // Tamanho máximo do heap
  bool prior; // Variável que define se a fila vai remover de acordo com a piroridade
              // ou tempo de chegada
};

typedef struct FILAESPERA* FilaEspera;

// Aloca a memória que irá guardar as estruturas iniciais de uma fila de espera
// e retorna o valor do apontador
FilaEspera criaFilaEspera();

// Coloca um novo item na fila. Faz nada caso item inserido seja NULL
void enfilaEspera(FilaEspera fila, Link node);

// Remove um item da fila e o retorna, caso a fila esteja vazia, retorna NULL.
// Caso prior == false,retira um item de acordo com a ordem de chegada, e de acordo
// com a prioridade caso prior == true
Link desenfilaEspera(FilaEspera fila);

// Retorna se a fila está vazia
bool vaziaEspera(FilaEspera fila);

// Retorna o numero de itens na fila
int tamEspera(FilaEspera fila);

// Conta quantos processos de cada prioridade existem na fila e retorna um vetor alocado
// com essa informação (É necessário liberar a memória desse vetor)
unsigned int* contagemEspera(FilaEspera fila);

// Aumenta o tempo de permanência do processo na fila, dependendo do parâmetro
// de qual fila ele se encontra
void timeAddEspera(FilaEspera fila);

// Imprime as informações principais de cada componente da fila
void printFilaEspera(FilaEspera fila);

// Libera toda a memória alocada para o armazenamento da fila, inclusive a mesma
void liberaFilaEspera(FilaEspera fila);

#endif