#include <stdlib.h>
#include <stdio.h>

#define SIZE (4294967296 / 512)

#define   HASHADD(var, val) ((var) = (((var) << 6) + (var)) + (val))
#define HASHCHECK(var, val) (((var)[((val) / 8) % (SIZE / 8)] & (2 << ((val) % 8))) > 0)
#define   TOLOWER(l)        (((l) >= 'A' && (l) <= 'Z') ? (l) - ('A' - 'a') : (l))

void __attribute__ ((noreturn)) die(const char s[]) {
	printf("Error: %s\n", s);
	exit(1);
}
