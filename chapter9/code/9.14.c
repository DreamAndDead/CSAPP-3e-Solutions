/*
 * 9.14.c
 */
#include <stdio.h>
#include <assert.h>
#include "vm/csapp.h"

int test(char* filename, char* content) {
  int fd;
  char buf[20];
  fd = Open(filename, O_RDONLY, 0);
  Read(fd, buf, strlen(content));
  return !strncmp(buf, content, strlen(content));
}

int touch(char* filename, char* content) {
  int fd;
  umask(DEF_UMASK);
  fd = Open(filename, O_WRONLY|O_CREAT|O_TRUNC, DEF_MODE);
  Write(fd, content, strlen(content));
  Close(fd);
}

int main(int argc, char* argv[]) {
  touch("hello.txt", "Hello, world!");
  assert(test("hello.txt", "Hello, world!"));

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

  assert(test("hello.txt", "Jello, world!"));
  return 0;
}


