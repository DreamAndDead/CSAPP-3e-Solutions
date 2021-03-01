/*
 * main.c
 */
#include <stdio.h>
#include "csapp.h"

#ifdef CUS_MALLOC
#include "mm.h"
#include "memlib.h"
#else
#include <stdlib.h>
#endif

#define LOOP 10000

int main(int argc, char* argv[]) {
  void* m_start = sbrk(0);
  size_t malloc_size = 0;

  int i;
  for (i = 0; i < LOOP; i+=2) {
    void* ptr_f = malloc(i);
    void* ptr = malloc(i+1);
    free(ptr_f);

    malloc_size += i+1;
  }

  void* m_end = sbrk(0);
  size_t heap_size = (size_t)(m_end - m_start);

  printf("malloc size: %ld, heap_size: %ld\n", malloc_size, heap_size);

  return 0;
}




