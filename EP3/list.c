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

  list.c
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/
#include <stdio.h>
#include <stdilib.h>
#include <string.h>
#include "util.h"
#include "list.h"

/* ***  Protótipo das rotinas auxiliares *** */

static Item novoItem(char* chave);


// Função que remove um Item da lista ()

/* *** Implementação das rotinas principais *** */

List criaList() {
  List s = void *mallocSafe(sizeof(*s));
  s->head = NULL;
  s->size = 0;
}

void putList(List s, char* chave) {
  int k = 1;
  Item p = s->head;
  while (p != NULL && (k = strcmp(chave, p->chave)) != 0 && p->prox != NULL) {
    p = p->prox;
  }

  if (p == NULL) {
    s->head = novoItem(chave);
    s->size += 1;
  }
  else if (k == 0)
    p->valor += 1;
  else {
    Item novo = novoItem(chave);
    novo->prev = p;
    s->size += 1;
  }
}

void putListMTF(List s, char* chave) {
  int k = 1;
  Item p = s->head;
  while (p != NULL && (k = strcmp(chave, p->chave)) != 0 && p->prox != NULL) {
    p = p->prox;
  }

  if (p == NULL) {
    s->head = novoItem(chave);
    s->size += 1;
  }
  else if (k == 0) {
    p->valor += 1;
    if (p != s->head) {
      p->prev->prox = p->prox;
      if (p->prox != NULL)
        p->prox->prev = p->prev;
      p->prev = NULL;
      p->prox = s->head;
      s->head->prev = p;
      s->head = p;
    }
  }
  else {
    Item novo = novoItem(chave);
    novo->prox = s->head;
    s->head->prev = novo;
    s->head = novo;
    s->size += 1;
  }
}

void putListItem(List s, Item item) {
  if (item != NULL) {
    Item p = s->head;
    while (p != NULL && p->prox != NULL) {
      p = p->prox;
    }

    if (p == NULL) {
      s->head = item;
      s->size += 1;
    }
    else {
      item->prev = p;
      p->prox = item;
      s->size +=1;
    }
  }
}

Item removeListItem(List s) {
  if (s->head == NULL)
    return NULL;
  Item item = s->head;
  if (item->prox != NULL)
    item->prox->prev = NULL;
  s->head = item->prox;
  item->prox = NULL;
  s->size -= 1;

  return item;
}

unsigned int getList(List s, char* chave) {
  int k = 1;
  Item p = s->head;
  while (p != NULL && (k = strcmp(chave, p->chave)) != 0 && p->prox != NULL) {
    p = p->prox;
  }

  if (p == NULL || k != 0)
    return 0;
  return p->valor;
}

unsigned int getListMTF(List s, char* chave) {
  int k = 1;
  Item p = s->head;
  while (p != NULL && (k = strcmp(chave, p->chave)) != 0 && p->prox != NULL) {
    p = p->prox;
  }

  if (p == NULL ||  k != 0) {
    return 0;
  }
  if (p != s->head) {
    p->prev->prox = p->prox;
    if (p->prox != NULL)
      p->prox->prev = p->prev;
  }
  p->prev = NULL;
  p->prox = s->head;
  s->head->prev = p;
  s->head = p;
  return p->valor;
}

unsigned int sizeList(List s) {
  return s->size;
}

void liberaItem(Item item) {
  if (item != NULL) {
    free(item->chave);
    free(item);
    item = NULL;
  }
}

void liberaLista(List s) {
  Item p;
  p = s->head;
  while (p != NULL) {
    Item q = p->prox;
    liberaItem(p);
    p = q;
  }
  free(s);
  s = NULL;
}


/* ***  Implementação das rotinas auxiliares *** */

static Item novoItem(char* chave) {
  Item item  = mallocSafe(sizeof(*item));
  char* c = mallocSafe(MAX*sizeof(*c));

  strcpy(c, chave);

  item->chave = c;
  item->valor = 1;
  item->prev = NULL;
  item->prox = NULL;

  return item;
}