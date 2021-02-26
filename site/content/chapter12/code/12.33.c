/*
 * 12.33.c
 */
#include <stdio.h>
#include "csapp.h"

struct pack {
  char *s;
  int size;
  FILE *stream;
};

char *ptr = NULL;
int timeout = -1;

void *thread_read(void *vargp) {
  struct pack p = *(struct pack *)vargp;
  ptr = fgets(p.s, p.size, p.stream);
  timeout = 0;
}

void *thread_sleep(void *vargp) {
  Sleep(5);
  timeout = 1;
}

char *tfgets(char *s, int size, FILE *stream) {
  pthread_t tid_read;
  pthread_t tid_sleep;
  struct pack p;

  p.s = s;
  p.size = size;
  p.stream = stream;
  Pthread_create(&tid_read, NULL, thread_read, (void*)&p);

  Pthread_create(&tid_sleep, NULL, thread_sleep, NULL);

  // wait 2 thread race result
  while(timeout == -1) {}

  if (timeout == 1) {
    Pthread_cancel(tid_read);
    return NULL;
  } else {
    Pthread_cancel(tid_sleep);
    return ptr;
  }
}

int main(int argc, char* argv[]) {
  char buf[MAXLINE];

  if (tfgets(buf, MAXLINE, stdin) == NULL)
    printf("BOOM!\n");
  else
    printf("%s", buf);

  return 0;
}


