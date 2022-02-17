/*
 * srl-sra.c
 */

#include <stdio.h>
#include <assert.h>

int is_little_endian() {
	int x = 1;
	char *p = (char *) &x;
	return !!(*p);
}

/* logical shift right */
unsigned srl(unsigned x, int k) {
	/* Perform shift arithmetically */
	unsigned xsra = (int) x >> k;
	int w = sizeof(int) << 3;
	// unsigned mask = !!k * ((1 << (w - k)) - 1) - !k;
	unsigned mask = (2 << (w - k - 1)) - 1;
	return xsra & mask;
}

/* arithmetical shift right */
int sra(int x, int k) {
	/* Perform shift logically */
	int xsrl = (unsigned) x >> k;
	int w = sizeof(int) << 3;
	int top = (0 - k) & x;
	unsigned char *ptop = (unsigned char *) &top;
	ptop += is_little_endian() * (sizeof(int) - 1);
	int atop = *ptop << 1;
	unsigned char *patop = (unsigned char *) &atop;
	patop += is_little_endian() + (!is_little_endian()) * (sizeof(int) - 2);
	char cres = *patop;
	cres |= cres << 1; cres |= cres << 2; cres |= cres << 4;
	int res = cres;
	unsigned mask = res & ~((1 << (w - k)) - 1);
	return mask | xsrl;
}

int main(int argc, char* argv[]) {
  unsigned test_unsigned = 0x12345678;
  int test_int = 0x12345678;

  assert(srl(test_unsigned, 4) == test_unsigned >> 4);
  assert(sra(test_int, 4) == test_int >> 4);

  test_unsigned = 0x87654321;
	test_int = 0x87654321;

	assert (srl (test_unsigned, 4) == test_unsigned >> 4);
	assert (sra (test_int, 4) == test_int >> 4);
  
  return 0;
}
