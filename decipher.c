#include "common.h"

//#define DEBUG
//#define SHOWALL
//#define SHOWMATCH

int main(int argc, char *argv[]) {

	// Check valid arguments
	if (argc <= 1) die("Too few arguments");

	unsigned int hash;
	char c;

	// Parse words.dat
	FILE *fp = fopen("words.dat", "rb");
	if (fp == NULL) die("Coudn't open words.dat");
	unsigned char *out = malloc(SIZE / 8);
	unsigned int i = 0;
	while ((c = fgetc(fp)) != EOF) {
		out[i] = c;
		++i;
	}

	// Test word
	//#define TEST
	#ifdef TEST
	const char test[] = "THE";
	hash = 0;
	for (unsigned int i = 0; test[i] != '\0'; ++i) {
		HASHADD(hash, TOLOWER(test[i]));
	}
	printf("Test \"%s\": %u %s\n",
		test,
		hash,
		HASHCHECK(out, hash) ? "matched" : "didn't match"
	);
	#endif

	// Parse argv
	unsigned int words = argc - 1;
	for (int i = 1; i < argc; ++i) {
		for (int m = 0; 1; ++m) {
			c = argv[i][m];
			if (c == '\0') break;
			if (c == ' ')  ++words;
		}
	}
	#ifdef DEBUG
		printf("Words: %d\n", words);
	#endif

	// Calculate stuff
	struct letter {
		unsigned int shift;
		unsigned int matchcount;
		//unsigned int match[words];
	};
	struct letter letters[26];
	unsigned int word;
	for (unsigned int l = 0; l < 26; ++l) {
		letters[l].shift = l;
		letters[l].matchcount = 0;
		word = 0;
		hash = 0;
		for (int i = 1; i < argc; ++i) {
			for (int m = 0; 1; ++m) {
				c = argv[i][m];
				if (c == ' ' || c == '\0') {
					if (HASHCHECK(out, hash)) {
						letters[l].matchcount++;
						//letters[l].match[word] = 1;
						#ifdef DEBUG
							printf("Matched: L: %2u WORD: %2u HASH: %u\n", l, word, hash);
						#endif
					}/* else {
						letters[l].match[word] = 0;						
					}*/
					++word;
					hash = 0;
					if (c == '\0') break;
				} else {
					c = TOLOWER(c);
					if (c >= 'a' && c <= 'z') {
						c += l;
						if (c > 'z') c -= 26;
					}
					HASHADD(hash, c);
				}
			}
		}
	}

	// sort output
	int compare(const void *a, const void *b) {
		#define A (*(struct letter*)a)
		#define B (*(struct letter*)b)
		if (A.matchcount == B.matchcount) return 0;
		if (A.matchcount <  B.matchcount) return 1;
		return -1;
		#undef A
		#undef B
	}
	qsort(&letters, 26, sizeof(struct letter), compare);

	// print
	#ifdef SHOWALL
		for (unsigned int l = 0; l < 26; ++l) {
			if (letters[l].matchcount == 0) break;
			printf("+%2u: ", letters[l].shift);
	#else
		unsigned int l = 0;
		{
			printf("+%u: ", letters[l].shift);
	#endif
		//word = 0;
		for (int i = 1; i < argc; ++i) {
			for (int m = 0; 1; ++m) {
				c = argv[i][m];
				if (c == '\0') break;
				if (c == ' ') {
					/*if (letters[l].match[word] == 1) {
						printf("\x1b[32m");
					} else {
						printf("\x1b[0m");
					}*/
					++word;
				} else if (c >= 'a' && c <= 'z') {
					c += letters[l].shift;
					if (c > 'z') c -= 25;
				} else if (c >= 'A' && c <= 'Z') {
					c += letters[l].shift;
					if (c > 'Z') c -= 25;
				}
				putchar(c);
			}
			/*if (letters[l].match[word] == 1) {
				printf("\x1b[32m");
			} else {
				printf("\x1b[0m");
			}
			++word;*/
			putchar(' ');

		}
		#ifdef SHOWMATCH
			printf("\x1b[0m(%d)\n", letters[l].matchcount);
		#else
			printf("\x1b[0m\n");
		#endif
	}

	return 0;
}
