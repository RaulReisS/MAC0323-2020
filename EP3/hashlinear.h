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

  hashlinear.h
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/
#ifndef _HASHLINEAR
#define _HASHLINEAR

#define START 300
#define TAM 101

// Estrutura para um hash com sondagem linear
struct CASA
{
    char* chave;
    unsigned int valor;
};

typedef struct CASA* Casa;

struct HASHLINEAR
{
    Casa *st;
    unsigned int n;
    unsigned int m;
};

typedef struct HASHLINEAR* HashLin; 

/* *** Protótipo das rotinas para a ávore binária de busca *** */

// Função que aloca a estrutura inicial de uma Tabela de Símbolos com Hash e condagem linear
HashLin criaHashLin();

// Função que insere um item na tabela com valor 1. Caso a chave já esteja na tabela, será
// adicionado 1 no valor
void putHashLin(HashLin hst, char* chave);

// Função que retorna o valor associado a uma determinada chave. Se a chave não estiver na st,
// então o valor retornado será 0
unsigned int getHashLin(HashLin hst, char* chave);

// Função que retorna quantos itens temos na tabela
unsigned int sizeHashLin(HashLin hst);

// Função que libera a memória utilizada pela tabela de hahs com sondagem linear
void liberaHashLin(HashLin hst);

#endif