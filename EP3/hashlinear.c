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

  hashlinear.c
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "hashlinear.h"

/* ***  Protótipo das rotinas auxiliares *** */

// Função que calcula o valor de hash dado uma detarminada chave e o tamanho da
// tabela
static int hash(char* chave, unsigned int m);

// Função que reajusta o tamanho do vetor da tabela de hash
static void resize(HashCad hst, unsigned int size);

// Função que compara as chaves de duas casas do vetor
static int compare(char* a, char* b);

// Função que aloca a memória para uma nova casa no vetor
static Casa novaCasa(char* chave);

// Função que libera a memória utilizada por uma casa do vetor
static void liberaCasa(Casa casa);

/* *** Implementação das rotinas principais *** */

HashLin criaHashLin() {
    HashLin hst = mallocSafe(sizeof(*hst));
    Casa *st = mallocSafe(START*sizeof(*st));

    for (int i = 0; i < START; i++)
        st[i] = NULL;

    hst->st = st;
    hst->n = 0;
    hst->m = START;

    return hst;
}

void putHashLin(HashLin hst, char* chave) {
    if (hst->n <= (hst->m)/2)
        resize(hst, 2*m);

    int h = 0;
    for (h = hash(chave, hst->m); hst->st[h] != NULL; h = (h+1) % hst->m)
        if (compare(hst->st[h]->chave, chave) == 0) {
            hst->st[h]->valor += 1;
            return;
        }
    hst->st[h] = novaCasa(chave);
    hst->n += 1;
}

unsigned int getHashLin(HashLin hst, char* chave) {
    int h;
    for (h = hash(chave, hst->m); hst->st[h] != NULL; h = (h+1) % hst->m)
        if (compare(hst->st[h]->chave, chave) == 0)
            return hst->st[h]->valor;
    return 0;
}

unsigned int sizeHashLin(HashLin hst) {
    return hst->n;
}

void liberaHashLin(HashLin hst) {
    for (int i = 0; i < hst->m; i++)
        liberaCasa(hst->st[i]);
    free(hst);
    hst = NULL;
}

/* ***  Implementação das rotinas auxiliares *** */

static int hash(char* chave, unsigned int m) {
    int h = 0;
    int tam = strlen(chave);
    for (int i = 0; i < tam; i++)
        h = (31 * h + chave[i]) % m

    return h;
}

static void resize(HashCad hst, unsigned int size) {
    Casa *novo = mallocSafe(size*sizeof(*novo));

    for(int i = 0; i < hst->m; i++) {
        if (hst->st[i] != NULL) {
            int h = hash(hst->st[i]->chave, size);
            while (novo[h] != NULL) {
                h = (h+1) % size;
            }
            novo[h] = hst->st[i];
        }
    }

    free(hst->st);
    hst->st = novo;
    hst->m = size;
}

static int compare(char* a, char* b) {
    if(a == NULL || b == NULL)
        return 1;
    return strcmp(a, b);
}

static Casa novaCasa(char* chave) {
    Casa casa = mallocSafe(sizeof(*casa));
    char* c = mallocSafe(TAM*sizeof(*c));

    strcpy(c, chave);

    casa->chave = chave;
    casa->valor = 1;

    return casa;
}

static void liberaCasa(Casa casa) {
    if (casa != NULL) {
        free(casa->chave);
        free(casa);
        casa = NULL;
    }
}