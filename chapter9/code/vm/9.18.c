/*
 * 9.18.c
 */
#include <stdio.h>
#include "csapp.h"
#include "mm.h"
#include "memlib.h"

#define LOOP 1000

int main(int argc, char* argv[]) {
  int i;
  for (i = 0; i < LOOP; i+=2) {
    void* ptr_f = mm_malloc(i);
    void* ptr = mm_malloc(i+1);
    mm_free(ptr_f);
  }

  return 0;
}



