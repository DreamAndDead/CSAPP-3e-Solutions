/*
 * 10.8.c
 */
#include <stdio.h>
#include "csapp.h"


int main(int argc, char* argv[]) {
  struct stat stat;
  char *type, *readok;

  int fd;
  if (argc <= 1)
    fd = 0; // stdin
  else
    fd = atoi(argv[1]);

  Fstat(fd, &stat);

  if (S_ISREG(stat.st_mode))
    type = "regular";
  else if (S_ISDIR(stat.st_mode))
    type = "dir";
  else
    type = "other";
  if ((stat.st_mode & S_IRUSR))
    readok = "yes";
  else
    readok = "no";

  printf("type: %s, read: %s\n", type, readok);

  return 0;
}


