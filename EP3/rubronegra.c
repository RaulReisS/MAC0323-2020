#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "rubronegra.h"

/* ***  Protótipo das rotinas auxiliares *** */

// Função que aloca a memória para um novo Node
static Link novoNode(char* chave);

// Função recursiva para a inserção de um item na árvore
static Link putTree(Link r, char* chave);

// Função recursiva para busca de um item na árvore
static Link getTree(Link r, char* chave);

// Função recursiva para a liberação da memória de uma árvore
static void freeNode(Link x);

// Função que verifica se um nó é rubro
static bool isRed(Link x);

// Função que rotaciona os nós da árvore para a esquerda em torno de um dado nó
static Link rotateLeft(Link h);

// Função que rotaciona os nós da árvore para a direita em torno de um dado nó
static Link rotateRight(Link h);

// Função que troca as cores de um nó pelas cores dos seus filhos e vice-versa
static void flipColors(Link h);

// Função que balenceia a estrutura em torno de um nó dado, caso necessário.
// (Mantém as invariantes de uma estrutura rubro-negra)
static Link balance(Link h);

// Variável global auxiliar
static unsigned int tam;


/* *** Implementação das rotinas principais *** */

RubroNegra criaRubroNegra() {
	RubroNegra t = mallocSafe(sizeof(*t));

	t->root = NULL;
	t->size = 0;

	return t;
}

void putRubroNegra(RubroNegra t, char* chave) {
	tam = t->size;
	t->root = putTree(t->root, chave);
	t->size = tam;
	t->root->color = BLACK;
}

unsigned int sizeRubroNegra(RubroNegra t) {
	return t->size;
}

unsigned int getRubroNegra(RubroNegra t, char* chave) {
	Link x = getTree(t->root, chave);
	if (x == NULL)
		return 0;
	return x->valor;
}

void liberaRubroNegra(RubroNegra t) {
	freeNode(t->root);
	free(t);
	t = NULL;
}

/* ***  Implementação das rotinas auxiliares *** */

static Link novoNode(char* chave) {
	Link p = mallocSafe(sizeof(*p));
	char *c = mallocSafe(MAX*sizeof(*c));

	strcpy(c, chave);

	p->chave = c;
	p->valor = 1;
	p->color = RED;
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
	if (cmp > 0)
		r->right = putTree(r->right, chave);
	else
		r->valor += 1;

	r = balance(r);

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

static bool isRed(Link x) {
	if (x == NULL || x->color == BLACK)
		return false
	return true;
}

static Link rotateLeft(Link h) {
	Link x = h->right;
	h->right = x->left;
	x->left = h;
	x->color = h->color;
	h->color = RED;
	return x;
}

static Link rotateRight(Link h) {
	Link x = h->left;
	h->left = x->right;
	x->right = h;
	x->color = h->color;
	h->color = RED;
	return x;
}

static void flipColors(Link h) {
	h->color = RED;
	h->left->color = BLACK;
	h->right->color = BLACK;
}

static Link balance(Link h) {
	if (isRed(h->right) && !isRed(h->left))
		h = rotateLeft(h);
	if (isRed(h->left) && isRed(h->left->left))
		h = rotateRight(h);
	if (isRed(h->left) && isRed(h->right))
		flipColors(h);
	return h;
}