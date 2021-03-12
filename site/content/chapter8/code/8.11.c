/*
 * 8.11.c
 */
#include <stdio.h>
#include "csapp.h"

int main(int argc, char* argv[]) {
  int i;

  for (i = 0; i < 2; i++)
    Fork();
  printf("hello\n"); fflush(stdout);
  exit(0);
}


