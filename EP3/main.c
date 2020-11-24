#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <time.h>
#include "bst.h"
#include "rubronegra.h"
#include "hashencadeado.h"
#include "hashlinear.h"
#include "trie.h"

// Cria um arquivo temporário com as astring tratadas: todas
// em minúsculo sem caracteres especiais
static void criaTemp(char* arq);

// Apaga o arquivo temporário
static void removeTemp();

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Necessário passar o nome de um arquivo na linha de comando.\n");
		return 0;
	}

	char p[101];
	clock_t init, end;
	double time;
	FILE* fp;
	Bst t;
	RubroNegra rnt;
	HashCad hash, hashMTF;
	HashLin hashLin;
	Trie tst;

	criaTemp(argv[1]);

	printf("Teste de tempo criação (em milisegundos) de estrutura baseado no arquivo %s:\n", argv[1]);

	printf("  Para Árvore Binária de Busca: ");
	fp = fopen("tmp.txt", "r");
	init = clock();
	t = criaBst();
	while (fscanf(fp, "%s", p) != EOF)
		putBst(t, p);
	end = clock();
	fclose(fp);
	liberaBst(t);
	time = (double) (end - init) * 1000.0 / (double) CLOCKS_PER_SEC;
	printf("%.3g\n", time);

	printf("  Para Árvore Rubro-Negra: ");
	fp = fopen("tmp.txt", "r");
	init = clock();
	rnt = criaRubroNegra();
	while (fscanf(fp, "%s", p) != EOF)
		putRubroNegra(rnt, p);
	end = clock();
	fclose(fp);
	liberaRubroNegra(rnt);
	time = (double) (end - init) * 1000.0 / (double) CLOCKS_PER_SEC;
	printf("%.3g\n", time);

	printf("  Para Hashing com encadeamento: ");
	fp = fopen("tmp.txt", "r");
	init = clock();
	hash = criaHashCad();
	while (fscanf(fp, "%s", p) != EOF)
		putHashCad(hash, p);
	end = clock();
	fclose(fp);
	liberaHashCad(hash);
	time = (double) (end - init) * 1000.0 / (double) CLOCKS_PER_SEC;
	printf("%.3g\n", time);

	printf("  Para Hashing com encadeamento e MTF: ");
	fp = fopen("tmp.txt", "r");
	init = clock();
	hashMTF = criaHashCad();
	while (fscanf(fp, "%s", p) != EOF)
		putHashCadMTF(hashMTF, p);
	end = clock();
	fclose(fp);
	liberaHashCad(hashMTF);
	time = (double) (end - init) * 1000.0 / (double) CLOCKS_PER_SEC;
	printf("%.3g\n", time);

	printf("  Para Hashing com Sondagem Linear: ");
	fp = fopen("tmp.txt", "r");
	init = clock();
	hashLin = criaHashLin();
	while (fscanf(fp, "%s", p) != EOF)
		putHashLin(hashLin, p);
	end = clock();
	fclose(fp);
	liberaHashLin(hashLin);
	time = (double) (end - init) * 1000.0 / (double) CLOCKS_PER_SEC;
	printf("%.3g\n", time);

	printf("  Para Trie, implimentado com Trie Ternária: ");
	fp = fopen("tmp.txt", "r");
	init = clock();
	tst = criaTrie();
	while (fscanf(fp, "%s", p) != EOF)
		putTrie(tst, p);
	end = clock();
	fclose(fp);
	liberaTrie(tst);
	time = (double) (end - init) * 1000.0 / (double) CLOCKS_PER_SEC;
	printf("%.3g\n", time);

	removeTemp();

	return 0;
}

static void criaTemp(char* arq) {
	FILE* fp = fopen(arq, "r");
	FILE* fq = fopen("tmp.txt", "w");
	char p[101];
	int d = 'a' - 'A';

	while(fscanf(fp, "%s", p) != EOF) {
		for(int i = 0; i < strlen(p); i++) {
			if (p[i] >= 'A' && p[i] <= 'Z')
				fprintf(fq, "%c", p[i]-d);
			else if (p[i] >= 'a' && p[i] <= 'z')
				fprintf(fq, "%c\n", p[i]);
		}
		fprintf(fq, " ");
	}

	fclose(fp);
	fclose(fq);
}

static void removeTemp() {
	remove("tmp.txt");
}