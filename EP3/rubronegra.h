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

  rubronegra.h
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/
#ifndef _RUBRONEGRA
#define _RUBRONEGRA

#include <stdbool.h>

// Definição de cor
#define BLACK false
#define RED true
#define MAX 101

typedef bool Cor;

// Estruturas para a árvore rubro-negra
typedef struct Nodern* Linkrn;

struct Nodern
{
  char *chave;
  unsigned int valor;
  Cor color;
  Linkrn left, right;
};

struct RUBRONEGRA
{
  Linkrn root;
  unsigned int size;
};

typedef struct RUBRONEGRA* RubroNegra;

/* *** Protótipo das rotinas para a ávore binária de busca rubro-negra *** */

// Função que aloca a estrutura inicial de uma Árvore binária de busca Rugro-negra
RubroNegra criaRubroNegra();

// Função que insere um item na árvore com valor 1. Caso a chave já esteja na
// ávore, será adicionado 1 no valor
void putRubroNegra(RubroNegra t, char* chave);

// Função que retornar o tamanho (número de nós) de uma dada árvore
// (ou seja, quantas palavras distintas)
unsigned int sizeRubroNegra(RubroNegra t);

// Função que obtém o valor de uma chave da bst rubro-negra. Caso a chave não
// esteja na árvore, o valor retornado será 0
unsigned int getRubroNegra(RubroNegra t, char* chave);

// Função que libera a memória que está alocando uma árvore
void liberaRubroNegra(RubroNegra t);

void printarvore(RubroNegra t);

#endif