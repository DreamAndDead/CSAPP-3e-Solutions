/*
 * 9.14.c
 */
#include <stdio.h>
#include "vm/csapp.h"

int main(int argc, char* argv[]) {
  struct stat stat;
  int fd;
  char* bufp;
  size_t size;

  fd = Open("hello.txt", O_RDWR, 0);
  fstat(fd, &stat);
  size = stat.st_size;

  bufp = Mmap(NULL, size, PROT_WRITE, MAP_SHARED, fd, 0);
  *bufp = 'J';
  Munmap(bufp, size);

  return 0;
}


