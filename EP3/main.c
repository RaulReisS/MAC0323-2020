#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bst.h"
#include "rubronegra.h"
#include "hashencadeado.h"
#include "hashlinear.h"
#include "trie.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Necessário passar o nome de um arquivo na linha de comando.\n");
		return 0;
	}

	FILE* fp;
	Bst t;
	RubroNegra rbt;
	HashCad hash, hashMTF;
	HashLin hashLin;
	Trie tst;
	unsigned int k, n;
	char p[101];

	printf("Para Árvore Binária de Busca:\n");
	fp = fopen(argv[1], "r");
	t = criaBst();
	n = 0;
	while (fscanf(fp, "%s", p) != EOF) {
		n++;
		putBst(t, p);
	}

	printf("n = %d\n", n);
	printf("size = %d\n", sizeBst(t));

	k = getBst(t, "porra");
	printf("porra = %d\n", k);

	fclose(fp);
	liberaBst(t);

	///////////////////////////////////
	printf("\nPara Árvore Rubro-Negra:\n");
	fp = fopen(argv[1], "r");
	rbt = criaRubroNegra();
	n = 0;
	while (fscanf(fp, "%s", p) != EOF) {
		n++;
		putRubroNegra(rbt, p);
	}

	printf("n = %d\n", n);
	printf("size = %d\n", sizeRubroNegra(rbt));

	k = getRubroNegra(rbt, "porra");
	printf("porra = %d\n", k);

	// printarvore(rbt);

	fclose(fp);
	liberaRubroNegra(rbt);

	printf("\nPara Hashing com encadeamento\n");
	fp = fopen(argv[1], "r");
	hash = criaHashCad();
	n = 0;
	while (fscanf(fp, "%s", p) != EOF) {
		n++;
		putHashCad(hash, p);
	}

	printf("n = %d\n", n);
	printf("size = %d\n", sizeHashCad(hash));

	k = getHashCad(hash, "porra");
	printf("porra = %d\n", k);

	fclose(fp);
	liberaHashCad(hash);

	printf("\nPara Hashing com encadeamento e MTF\n");
	fp = fopen(argv[1], "r");
	hashMTF = criaHashCad();
	n = 0;
	while (fscanf(fp, "%s", p) != EOF) {
		n++;
		putHashCadMTF(hashMTF, p);
	}

	printf("n = %d\n", n);
	printf("size = %d\n", sizeHashCad(hashMTF));

	k = getHashCad(hashMTF, "porra");
	printf("porra = %d\n", k);

	fclose(fp);
	liberaHashCad(hashMTF);

	printf("\nPara Hashing com Sondagem Linear\n");
	fp = fopen(argv[1], "r");
	hashLin = criaHashLin();
	n = 0;
	while (fscanf(fp, "%s", p) != EOF) {
		n++;
		putHashLin(hashLin, p);
	}

	printf("n = %d\n", n);
	printf("size = %d\n", sizeHashLin(hashLin));

	k = getHashLin(hashLin, "porra");
	printf("porra = %d\n", k);

	fclose(fp);
	liberaHashLin(hashLin);

	printf("\nPara Trie, implimentado com Trie ternária\n");
	fp = fopen(argv[1], "r");
	tst = criaTrie();
	n = 0;
	while (fscanf(fp, "%s", p) != EOF) {
		n++;
		putTrie(tst, p);
	}

	printf("n = %d\n", n);
	printf("size = %d\n", sizeTrie(tst));

	k = getTrie(tst, "porra");
	printf("porra = %d\n", k);

	fclose(fp);
	liberaTrie(tst);

	return 0;
}