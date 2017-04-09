/*
 * show-bytes.c
 *
 * linux:
 *   gcc -m64 show-bytes.c
 * or
 *   gcc -m32 show-bytes.c
 * run it
 *   ./a.out
 */

#include <stdio.h>

typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
  size_t i;
  for (i = 0; i < len; i++) {
    printf(" %.2x", start[i]);
  }
  printf("\n");
}

void show_int(int x) {
  show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
  show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void* x) {
  show_bytes((byte_pointer) &x, sizeof(void*));
}

void test_show_bytes(int val) {
  int ival = val;
  float fval = (float) ival;
  int* pval = &ival;

  show_int(ival);
  show_float(fval);
  show_pointer(pval);
}

int main(int argc, char* argv[]) {
  int test_num = 328;
  test_show_bytes(test_num);
  return 0;
}


