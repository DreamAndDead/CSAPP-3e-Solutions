/*
 * 12.21.c
 */
#include <stdio.h>
#include "csapp.h"

#define WRITE_LIMIT 100000
#define PEOPLE 4

static int readtimes;
static int writetimes;
static int writecnt;
sem_t mutex, w;

static int number;

void *reader(void *vargp) {
  while (1) {
    // writer first
    if (writecnt > 0)
      continue;

    P(&w);

    /* Critical section */
    readtimes++;
    /* Critical section */

    V(&w);
  }
}

void *writer(void *vargp) {
  while (1) {
    P(&mutex);
    // one more writer wait to write
    writecnt++;
    V(&mutex);

    P(&w);

    /* Critical section */
    writetimes++;
    if (writetimes == WRITE_LIMIT) {
      printf("read/write: %d/%d\n", readtimes, writetimes);
      exit(0);
    }
    /* Critical section */

    V(&w);

    P(&mutex);
    // writer has written
    writecnt--;
    V(&mutex);
  }
}

void init(void) {
  writecnt = 0;
  readtimes = 0;
  writetimes = 0;
  Sem_init(&w, 0, 1);
  Sem_init(&mutex, 0, 1);
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

