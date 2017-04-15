/*
 * calloc.c
 */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* rename to avoid conflict */
void* another_calloc(size_t nmemb, size_t size) {
  if (nmemb == 0 || size == 0) {
    return NULL;
  }
  size_t buf_size = nmemb * size;
  /* a good way to check overflow or not */
  if (nmemb == buf_size / size) {
    void* ptr = malloc(buf_size);
    memset(ptr, 0, buf_size);
    return ptr;
  }
  return NULL;
}

int main(int argc, char* argv[]) {
  void* p;
  p = another_calloc(0x1234, 1);
  assert(p != NULL);
  free(p);

  p = another_calloc(SIZE_MAX, 2);
  assert(p == NULL);
  free(p);
  return 0;
}


