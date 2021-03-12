/*
 * mm_first_fit.c
 *
 * test example code from book section 9.9.12
 */
#include <stdio.h>
#include <assert.h>
#include "csapp.h"
#include "mm.h"
#include "memlib.h"

/*
 * blk
 * vvv
 * 1    2    3    4    5        6
 * +----+----+----+----+--------+--------+
 * |    ||||||    ||||||        ||||||||||
 * +----+----+----+----+--------+--------+
 * 1         3         2
 * ^^^
 * new_blk
 */
int main(int argc, char* argv[]) {

  // allocate 8 bytes because of alignment
  void* blk_1 = mm_malloc(1);
  void* blk_2 = mm_malloc(1);

  void* blk_3 = mm_malloc(8);
  void* blk_4 = mm_malloc(8);
  void* blk_5 = mm_malloc(16);
  void* blk_6 = mm_malloc(16);

  mm_free(blk_1);
  mm_free(blk_3);
  mm_free(blk_5);


  void* new_blk_1 = mm_malloc(6);
  void* new_blk_2 = mm_malloc(12);
  void* new_blk_3 = mm_malloc(7);

  assert(new_blk_1 == blk_1);
  assert(new_blk_2 == blk_5);
  assert(new_blk_3 == blk_3);

  return 0;
}




