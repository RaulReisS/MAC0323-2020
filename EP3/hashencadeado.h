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

  hashencadeado.h
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/
#ifndef _HASHENCADEADO
#define _HASHENCADEADO

#include "list.h"
#define INIT 43

// Estrutura para um hash com encadeamento
struct HASHENCADEADO
{
	List st;
	unsigned int n;
	unsigned int m;
};

typedef HASHENCADEADO* HashCad;

/* *** Protótipo das rotinas para a ávore binária de busca *** */

// Função que aloca a estrutura inicial de uma Tabela de Símbolos com Hash por encadeamento
HashCad criaHashCad();

// Função que insere um item na tabela com valor 1. Caso a chave já esteja na árvore, será
// adicionado 1 no valor
void putHashCad(HashCad hst, char* chave);

// Função que insere um item na tabela com valor 1. Caso a chave já esteja na árvore, será
// adicionado 1 no valor. Esta versão utiliza Encadeamento com Move to Front.(MTF)
void putHashCadMTF(HashCad hst, char* chave);

// Função que retorna o valor associado a uma determinada chave. Se a chave não estiver na st,
// então o valor retornado será 0
void getHashCad(HashCad hst, char* chave);

// Função que retorna o valor associado a uma determinada chave. Se a chave não estiver na st,
// então o valor retornado será 0. Esta versão utiliza encadeamento com Move to Front (MTF)
void getHashCadMTF(HashCad hst, char* chave);

//Função que retorna quantos itens estão na tabela
unsigned int sizeHashCad(HashCad hst);

// Função que libera a memória utilizada pela tabela de hash com encadeamento
void liberaHashCad(HashCad hst);

#endif