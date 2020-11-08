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

  filaCPU.h
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/
#ifndef _FILACPU
#define _FILACPU

#include <stdbool.h>
#include <stdlib.h>
#include "node.h"

#define MAX 10
#define TIME 20
#define FWAIT 'w'
#define FCPU 'c'
#define FPRINT 'p'

struct FILA {
	Link head; // Apontador para o nó cabeça da fila
	unsigned int size; // Tamanho da fila
};

typedef struct FILA* Fila;

// Aloca a memória que irá guardar as estruturas iniciais de uma fila e retorna
// o valor do apontador
Fila criaFila();

// Coloca um novo item na fila (Não verifica se a fila está cheia). Faz nada
// caso item inserido seja NULL
void enfila(Fila fila, Link node);

// Remove um item da fila e o retorna, caso a fila esteja vazia, retorna NULL
Link desenfila(Fila fila);

// Retorna se a fila está vazia
bool vazia(Fila fila);

// Retorna se a fila está cheia, ou seja, se está na sua capacidade máxima (MAX)
bool cheia(Fila fila);

// Retorna o numero de itens na fila
int tam(Fila fila);

// Passa o primeiro item da fila para a última posição, restaurando o seu tempo
// de uso de CPU
void anda(Fila fila);

// Aumenta o tempo de permanência do processo na fila
void timeAdd(Fila fila, char nome);

// Avança uma unidade de tempo na CPU e realiza as ações necessárias. Retorna
// o processo que foi encerrado, ou NULL caso nenhum processo foi encerrado
Link clockCPU(Fila fila);

// Imprime as informações principais de cada componente da fila
void printFila(Fila fila);

// Libera toda a memória alocada para o armazenamento da fila, inclusive a mesma
void liberaFila(Fila fila);
#endif