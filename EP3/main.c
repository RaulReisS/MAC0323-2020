#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bst.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Necessário passar o nome de um arquivo na linha de comando.\n");
		return 0;
	}

	FILE* fp = fopen(argv[1], "r");
	Bst t = criaBst();
	unsigned int k, n = 0;
	char p[101];
	while (fscanf(fp, "%s", p) != EOF) {
		n++;
		putBst(t, p);
	}

	printf("n = %d\n", n);
	printf("size = %d\n", sizeBst(t));

	k = getBst(t, "porra");
	printf("porra = %d\n", k);

	liberaBst(t);
	return 0;
}