#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
	bool b = false;
	if (!b)
		printf("FALSE\n");
	b = true;
	if (b)
		printf("TRUE\n");
	return 0;
}