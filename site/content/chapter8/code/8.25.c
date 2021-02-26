/*
 * 8.25.c
 */
#include <stdio.h>
#include "csapp.h"

sigjmp_buf buf;

void handler(int sig) {
  /* jump */
  siglongjmp(buf, 1);
}

char* tfgets(char* s, int size, FILE* stream) {
  char* result;

  if (!sigsetjmp(buf, 1)) {
    alarm(5);
    if (signal(SIGALRM, handler) == SIG_ERR)
      unix_error("set alarm handler error");
    return fgets(s, size, stream);
  } else {
    /* run out of time */
    return NULL;
  }
}

#define LEN 100

int main(int argc, char* argv[]) {
  char buf[LEN];
  char* input = tfgets(buf, LEN, stdin);

  if (input == NULL) {
    printf("nothing input: NULL\n");
  } else {
    printf("%s", input);
  }
  return 0;
}


