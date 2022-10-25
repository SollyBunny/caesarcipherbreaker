
#include "common.h"

int main() {

	FILE  *fp = fopen("words.txt", "r");
	//fseek(fp, 0, SEEK_END);
	// /size_t fs = ftell(fp);
	//fseek(fp, 0, SEEK_SET);

	char c;
	unsigned int hash = 0;
	unsigned char *out = malloc(SIZE / 8);
	while ((c = fgetc(fp)) != EOF) {
		if (c == '\n') {
			out[(hash / 8) % (SIZE / 8)] |= 2 << (hash % 8);
			hash = 0;
		} else {
			HASHADD(hash, c);
		}
	}

	fclose(fp);

	fp = fopen("words.dat", "wb");
	fwrite(out, 1, SIZE / 8, fp);
	fclose(fp);

	return 0;
}
