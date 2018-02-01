/*
 * 9.18.c
 */
#include <stdio.h>
#include <assert.h>
#include "csapp.h"
#include "mm.h"
#include "memlib.h"

/*
 * blk
 * vvv
 * 1       2           3
 * +-------+-----------+---------+
 * |||||||||           |||||||||||
 * +-------+-----------+---------+
 */

// current block head
unsigned int blk_head(void* blk) {
  unsigned int * header = (unsigned int *)blk - 1;
  return *header;
}

// previous block tail
unsigned int prev_blk_tail(void* blk) {
  unsigned int * prev_tail = (unsigned int *)blk - 2;
  return *prev_tail;
}

// if block is allocated
int blk_alloc(void* blk) {
  return blk_head(blk) & 0x1;
}

// if previous block is allocated
int blk_prev_alloc(void* blk) {
  return (blk_head(blk) & 0x2) >> 1;
}

int rand_num(void) {
  return rand() % 10000;
}

int main(int argc, char* argv[]) {
  void* blk_1 = mm_malloc(rand_num());
  void* blk_2 = mm_malloc(rand_num());
  void* blk_3 = mm_malloc(rand_num());
  mm_free(blk_2);


  assert(blk_alloc(blk_1));
  assert(!blk_alloc(blk_2));
  assert(blk_alloc(blk_3));

  assert(blk_prev_alloc(blk_1));
  assert(blk_prev_alloc(blk_2));
  assert(!blk_prev_alloc(blk_3));


  assert(blk_head(blk_1) != prev_blk_tail(blk_2));
  assert(blk_head(blk_2) == prev_blk_tail(blk_3));

  return 0;
}



