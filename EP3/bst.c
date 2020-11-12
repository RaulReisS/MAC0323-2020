#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "bst.h"

/* ***  Protótipo das rotinas auxiliares *** */

// Função que aloca a memória para um novo Nove
static Link novoNode(char* chave);

// Função recursiva para a inserção de um item na árvore
static Link putTree(Link r, char* chave);

// Função recursiva para busca de um item na árvore
static Link getTree(Link r, char* chave);

// Função recursiva para a liberação da memória de uma árvore
static void freeNode(Link x);

/* *** Rotinas principais *** */

unsigned int tam;

Bst criaBst() {
	Bst t = mallocSafe(sizeof(*t));

	t->root = NULL;
	t->size = 0;

	return t;
}

void putBst(Bst t, char* chave) {
	tam = t->size;
	t->root = putTree(t->root, chave);
	t->size = tam;
}

unsigned int sizeBst(Bst t) {
	return t->size;
}

unsigned int getBst(Bst t, char* chave) {
	Link x = getTree(t->root, chave);
	if (x == NULL)
		return 0;
	return x->valor;
}

void LiberaBst(Bst t) {
	freeNode(t->root);
	free(t);
}

/* ***  Implementação das rotinas auxiliares *** */

static Link novoNode(char* chave) {
	Link p = mallocSafe(sizeof(*p));
	char *c = mallocSafe(MAX*sizeof(*c));

	strcpy(c, chave);

	p->chave = c;
	p->valor = 1;
	p->left = NULL;
	p->right = NULL;

	return p;
}

static Link putTree(Link r, char* chave) {
	if (r == NULL) {
		tam++;
		return novoNode(chave);
	}

	int cmp = strcmp(chave, r->chave);

	if (cmp < 0)
		r->left = putTree(r->left, chave);
	else if (cmp > 0)
		r->right = putTree(r->right, chave);
	else
		r->valor += 1;
	
	return r;
}

static Link getTree(Link r, char* chave) {
	if (r == NULL)
		return NULL;

	int cmp = strcmp(chave, r->chave);

	if (cmp < 0)
		return getTree(r->left, chave);
	if (cmp > 0)
		return getTree(r->right, chave);
	return r;
}

static void freeNode(Link x) {
	if (x != NULL) {
		freeNode(x->left);
		freeNode(x->right);
		free(x->chave);
		free(x);
	}
}
