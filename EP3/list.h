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

  list.h
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/
#ifndef _LIST
#define _LIST

// Estruturas para uma lista
#define MAX 101

typedef struct ITEM* Item;

struct ITEM
{
  char* chave;
  unsigned int valor;
  Item prev, prox;
};

struct LISTA
{
  Item head;
  unsigned int size;
};

typedef struct LISTA* List;

/* *** Protótipo das rotinas para Lista *** */

// Funço que aloca a estrutura inicial necessária para uma Lista
List criaList();

// Função que insere um item na lista
void putList(List s, char* chave);

// Função que insere um item na lista utilizando a técnica Move to Front (MTF)
void putListMTF(List s, char* chave);

// Função que insere diretamente um Item na lista
void putListItem(List s, Item item);

// Função que remove diretamente o primeiro Item da lista (Útil para fazer rehashing)
Item removeListItem(List s);

// Função que obtém o valor associado à uma chave da lista e retorna 0 caso
// o item não esteja na mesma
unsigned int getList(List s, char* chave);

// Função que obtém o valor associado à uma chave da lista e retorna 0 caso
// o item não esteja na mesma, porém utilizando a técnica Move to Front (MTF)
unsigned int getListMTF(List s, char* chave);

// Função que retorna o tamanho da lista
unsigned int sizeList(List s);

// Função que libera a memória utilizada por um Item
// (Caso o cliente faça a remoção direta do Item)
void liberaItem(Item item);

// Função que libera a memória utilizada por uma lista
void liberaLista(List s);

void printList(List s);

#endif