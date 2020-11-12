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

  bst.h
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/
#ifndef _BST
#define _BST

#define MAX 101
// Estruturas para a árvore binária de busca
typedef struct Node* Link;

struct Node
{
	char *chave;
	unsigned int valor;
	Link left, right;
};

struct BST
{
	Link root;
	unsigned int size;
};

typedef struct BST *Bst;

/* *** Protótipo das rotinas para a ávore binária de busca *** */

// Função que aloca a estrutura inicial de uma Árbore binária de busca
Bst criaBst();

// Função que insere um item na árvore com valor 1. Caso a chave já esteja na
// árvore será adicionado 1 no valor
void putBst(Bst t, char* chave);

// Função que retorna o tamanho (Número de nós) de uma dada árvore
// (Ou seja, quantas palavras distintas)
unsigned int sizeBst(Bst t);

// Função que obtem o valor de uma chave da Bst. Caso a chave não esteja na
// árvore, o valor retornado será 0
unsigned int getBst(Bst t, char* chave);

// Função que libera a memória que está alocando uma árvore
void LiberaBst(Bst t);

#endif