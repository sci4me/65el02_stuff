#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
	FILE *fh = fopen(argv[1], "a+");
	if(!fh) {
		fprintf(stderr, "Could not open file!\n");
		return 1;
	}

	fseek(fh, 0L, SEEK_END);
	int b = ftell(fh);
	b = (b / 128 + 1) * 128 - b;

	char *zb = calloc(1, b);
	fwrite(zb, 1, b, fh);
	fflush(fh);
	fclose(fh);

	free(zb);

	return 0;
}