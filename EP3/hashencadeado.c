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

  hashencadeado.c
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "hashencadeado.h"

/* ***  Protótipo das rotinas auxiliares *** */

// Função que calcula o valor de hash dado uma detarminada chave e o tamanho da
// tabela
static int hash(char* chave, unsigned int m);

// Função que reajusta o tamanho do vetor da tabela de hash
static void resize(HashCad hst, unsigned int size);

/* *** Implementação das rotinas principais *** */

HashCad criaHashCad() {
  HashCad hst = mallocSafe(sizeof(*hst));
  List *st = mallocSafe(INIT*sizeof(*st));
  for (int i = 0; i < INIT; i++)
    st[i] = NULL;

  hst->st = st;
  hst->n = 0;
  hst->m = INIT;

  return hst;
}

void putHashCad(HashCad hst, char* chave) {

  if (hst->n >= 11 * hst->m)
    resize(hst, 3 * hst->m);
  int h = hash(chave, hst->m);
  int k = 0;

  if (hst->st[h] == NULL)
    hst->st[h] = criaList();

  k = sizeList(hst->st[h]);
  putList(hst->st[h], chave);
  if (k != sizeList(hst->st[h]))
    hst->n += 1;
}

void putHashCadMTF(HashCad hst, char* chave) {
  if (hst->n >= 11 * hst->m)
    resize(hst, 3 * hst->m);
  int h = hash(chave, hst->m);
  int k = 0;

  if (hst->st[h] == NULL)
    hst->st[h] = criaList();

  k = sizeList(hst->st[h]);
  putListMTF(hst->st[h], chave);
  if (k != sizeList(hst->st[h]))
    hst->n += 1; 
}

unsigned int getHashCad(HashCad hst, char* chave) {
  int h = hash(chave, hst->m);
  return getList(hst->st[h], chave);
}

unsigned int getHashCadMTF(HashCad hst, char* chave) {
  int h = hash(chave, hst->m);
  return getListMTF(hst->st[h], chave);
}

unsigned int sizeHashCad(HashCad hst) {
  return hst->n;
}

void liberaHashCad(HashCad hst) {
  for (int i = 0; i < hst->m; i++)
    liberaLista(hst->st[i]);
  free(hst);
  hst = NULL;
}

/* ***  Implementação das rotinas auxiliares *** */

static int hash(char* chave, unsigned int m) {
  int h = 0;
  int tam = strlen(chave); 
  for (int i = 0; i < tam; i++)
    h = (31 * h + chave[i]) % m;

  return h;
}

static void resize(HashCad hst, unsigned int size) {
  Item p = NULL;
  int h = 0;
  int aux = hst->m;
  hst->m = size;

  List *newSt = mallocSafe(size * sizeof(*newSt));
  for (h = 0; h < size; h++)
    newSt[h] = NULL;

  for (int i = 0; i < aux; i++) {
    while(sizeList(hst->st[i]) > 0) {
      p = removeListItem(hst->st[i]);
      h = hash(p->chave, size);
      if(newSt[h] == NULL)
        newSt[h] = criaList();
      putListItem(newSt[h], p);
    }
    liberaLista(hst->st[i]);
  }
  free(hst->st);
  hst->st = newSt;
}