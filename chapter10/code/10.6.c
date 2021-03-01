/*
 * 10.6.c
 */
#include <stdio.h>
#include "csapp.h"


int main(int argc, char* argv[]) {
  int fd1, fd2;

  fd1 = Open("foo.txt", O_RDONLY, 0);
  fd2 = Open("bar.txt", O_RDONLY, 0);
  Close(fd2);
  fd2 = Open("baz.txt", O_RDONLY, 0);
  printf("fd2 = %d\n", fd2);

  exit(0);
}


