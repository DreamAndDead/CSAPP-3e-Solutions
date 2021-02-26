/*
 * 9.17.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "csapp.h"
#include "mm.h"
#include "memlib.h"

/*
 * blk
 * vvv
 * 1      2      3         4
 * +------+------+---------+---------+............
 * ||||||||      |||||||||||         |............
 * +------+------+---------+---------+............
 *                         1         2
 * ^^^
 * new_blk
 */
int rand_num(void) {
  return rand() % 10000;
}

int main(int argc, char* argv[]) {

  void* blk_1 = mm_malloc(rand_num());
  void* blk_2 = mm_malloc(rand_num());
  void* blk_3 = mm_malloc(rand_num());
  void* blk_4 = mm_malloc(rand_num());
  mm_free(blk_2);
  mm_free(blk_4);

  void* new_blk_1 = mm_malloc(rand_num());
  void* new_blk_2 = mm_malloc(rand_num());

  assert(new_blk_1 != blk_2);
  assert(new_blk_1 == blk_4);
  assert(new_blk_2 != blk_2);
  assert(new_blk_2 != blk_4);

  return 0;
}



