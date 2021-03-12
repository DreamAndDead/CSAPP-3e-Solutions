/*
 * 12.20.c
 */
#include <stdio.h>
#include "csapp.h"

#define WRITE_LIMIT 100000
#define PEOPLE 20 // 10 reader and 10 writer
#define N 5

static int readtimes;
static int writetimes;
sem_t mutex;
sem_t readercnt;

void *reader(void *vargp) {
  while (1) {
    P(&readercnt);
    P(&mutex);

    readtimes++;

    V(&mutex);
    V(&readercnt);
  }
}

void *writer(void *vargp) {
  while (1) {
    P(&mutex);

    writetimes++;
    if (writetimes == WRITE_LIMIT) {
      printf("read/write: %d/%d\n", readtimes, writetimes);
      exit(0);
    }

    V(&mutex);
  }
}

void init(void) {
  readtimes = 0;
  writetimes = 0;
  Sem_init(&mutex, 0, 1);
  Sem_init(&readercnt, 0, N);
}


int main(int argc, char* argv[]) {
  int i;
  pthread_t tid;

  init();

  for (i = 0; i < PEOPLE; i++) {
    if (i%2 == 0)
      Pthread_create(&tid, NULL, reader, NULL);
    else
      Pthread_create(&tid, NULL, writer, NULL);
  }

  Pthread_exit(NULL);
  exit(0);
}



