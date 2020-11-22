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

  trie.c
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "trie.h"

/* ***  Protótipo das rotinas auxiliares *** */

// Função que aloca a memória necessária par um Nó
static No novoNo(char c);

// Função que libera a memória ocupada por um Nó e seus nós adjascentes (Recursivo)
static void liberaNo(No x);

// Função auxiliar recursiva para inserção de uma chave na Trie
static No putT(No x, char* chave, int d);

// Função auxiliar recursiva para busca de uma chave na Trie
static No getT(No x, char* chave, int d);

// Variável global auxiliar
static unsigned int insert;


/* *** Implementação das rotinas principais *** */

Trie criaTrie() {
    Trie tst = mallocSafe(sizeof(*tst));

    tst->root = NULL;
    tst->size = 0;

    return tst;
}

void putTrie(Trie tst, char* chave) {
    insert = 0;
    tst->root = putT(tst->root, chave, 0);
    tst->size += insert;
}

unsigned int getTrie(Trie tst, char* chave) {
    No x = getT(tst->root, chave, 0);
    if (x == NULL)
        return 0;
    return x->valor;
}

unsigned int sizeTrie(Trie tst) {
    return tst->size;
}

void liberaTrie(Trie tst) {
    liberaNo(tst->root);
    free(tst);
    tst = NULL;
}

/* ***  Implementação das rotinas auxiliares *** */

static No novoNo(char c) {
    No x = mallocSafe(sizeof(*x));
    x->c = c;
    x->valor = 0;
    x->left = NULL;
    x->right = NULL;
    x->mid = NULL;

    return x;
}

static void liberaNo(No x) {
    if (x != NULL) {
        liberaNo(x->left);
        liberaNo(x->mid);
        liberaNo(x->right);
        free(x);
        x = NULL;
    }
}

static No putT(No x, char* chave, int d) {
    char c = chave[d];

    if (x == NULL)
        x = novoNo(c);

    if (c < x->c)
        x->left = putT(x->left, chave, d);
    else if (c > x->c)
        x->right = putT(x->right, chave, d);
    else if (d < strlen(chave) - 1)
        x->mid = putT(x->mid, chave, d+1);
    else {
        if (x->valor == 0)
            insert = 1;
        x->valor += 1;
    }

    return x;
}

static No getT(No x, char* chave, int d) {
    char c = chave[d];

    if (x == NULL)
        return NULL;
    if (c < x->c)
        return getT(x->left, chave, d);
    if (c > x->c)
        return getT(x->right, chave, d);
    if (d < strlen(chave) - 1)
        return getT(x->mid, chave, d+1);

    return x;
}