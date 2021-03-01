/*
 * 12.32.c
 */
#include <stdio.h>
#include "csapp.h"

char *tfgets(char *s, int size, FILE *stream) {
  fd_set read_set;
  FD_ZERO(&read_set);
  FD_SET(STDIN_FILENO, &read_set);

  struct timeval timeout;
  timeout.tv_sec = 5;
  timeout.tv_usec = 0;

  Select(1, &read_set, NULL, NULL, &timeout);
  if (FD_ISSET(STDIN_FILENO, &read_set))
    return fgets(s, size, stream);
  else
    return NULL;
}

int main(int argc, char* argv[]) {
  char buf[MAXLINE];

  if (tfgets(buf, MAXLINE, stdin) == NULL)
    printf("BOOM!\n");
  else
    printf("%s", buf);

  return 0;
}


