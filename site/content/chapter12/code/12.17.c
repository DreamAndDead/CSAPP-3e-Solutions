/*
 * 12.17.c
 */
#include "csapp.h"
void *thread(void *vargp);

int main()
{
  pthread_t tid;

  Pthread_create(&tid, NULL, thread, NULL);
  // exit(0);
  Pthread_exit(NULL);
}

/* Thread routine */
void *thread(void *vargp)
{
  Sleep(1);
  printf("Hello, world!\n");
  return NULL;
}
