#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <libgen.h>

// a hex value that you need to put in-order to get the en/de coded value.
extern unsigned char key;

// start of function declarations:
unsigned char *xorEncode(const char *input, size_t len);
unsigned char *xorDecode(const unsigned char *input, size_t len);
uint64_t xor64FileHash(const char *filename);
void printUsage(const char *prog);
// end of function declarations: