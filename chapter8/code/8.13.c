/*
 * 8.13.c
 */
#include <stdio.h>
#include "csapp.h"

int main(int argc, char* argv[]) {
  int x = 3;

  if (Fork() != 0) {
    printf("x=%d\n", ++x);
  }

  printf("x=%d\n", --x);
  exit(0);
}


