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

  trie.h
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/
#ifndef _TRIE
#define _TRIE

// Estrutura para uma Trie (Ternária)
typedef struct NO* No;

struct NO
{
    char c;
    unsigned int valor;
    No left, mid, right;
};

struct TRIE
{
    No root;
    unsigned int size;
};

typedef struct TRIE* Trie;

/* *** Protótipo das rotinas para a ávore binária de busca *** */

// Função que aloca a estrutura inicial de uma Tabela de Símbolos com Strings
// utilizando Tries ternárias
Trie criaTrie();

// Função que insere um item na trie com valor 1. Caso a chave já esteja na tabela, será adicionado 1 no valor
void putTrie(Trie tst, char* chave);

// Função que retorna o valor associado a uma determinada chave. Se a chave não
// existir na Trie, o valor retornado será 0
unsigned int getTrie(Trie tst, char* chave);

// Função que retorna quantos chaves existem na Trie
unsigned int sizeTrie(Trie tst);

// Função que libera a memória utilizada pela Trie
void liberaTrie(Trie tst);

#endif