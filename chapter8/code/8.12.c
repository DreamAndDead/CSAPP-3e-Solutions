/*
 * 8.12.c
 */
#include <stdio.h>
#include "csapp.h"

void doit() {
  Fork();
  Fork();
  printf("hello\n"); fflush(stdout);
  return;
}

int main(int argc, char* argv[]) {
  doit();
  printf("hello\n"); fflush(stdout);
  return 0;
}


