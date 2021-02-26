/*
 * main.c
 */
#include <stdio.h>
#include "../csapp.h"
#include "tiny.h"
#include "sbuf.h"

#define SBUFSIZE  4
#define INIT_THREAD_N  1
#define THREAD_LIMIT 4096

static int nthreads;
static sbuf_t sbuf; /* Shared buffer of connected descriptors */

// thread info
typedef struct {
  pthread_t tid;
  sem_t mutex;
} ithread;

static ithread threads[THREAD_LIMIT];

// init work
void init(void);
// function for create server thread
void *serve_thread(void *vargp);
/*
 * creating thread that adjust total thread count according to sbuf situation
 *
 * if sbuf is empty, double threads
 * if sbuf is full, half threads
 */
void *adjust_threads(void *);
// from start to end, create (end - start) new server threads
void create_threads(int start, int end);

int main(int argc, char **argv) {
  int i, listenfd, connfd;
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;
  pthread_t tid;

  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    fprintf(stderr, "use default port 5000\n");
    listenfd = Open_listenfd("5000");
  } else {
    listenfd = Open_listenfd(argv[1]);
  }

  init();

  Pthread_create(&tid, NULL, adjust_threads, NULL);

  while (1) {
    clientlen = sizeof(struct sockaddr_storage);
    connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);
    sbuf_insert(&sbuf, connfd); /* Insert connfd in buffer */
  }
}

void init(void) {
  nthreads = INIT_THREAD_N;
  sbuf_init(&sbuf, SBUFSIZE);

  // create initail server threads
  create_threads(0, nthreads);
}

void *serve_thread(void *vargp) {
  int idx = *(int*)vargp;
  Free(vargp);

  while (1) {
    // get lock first
    // thread can't be kill now
    P(&(threads[idx].mutex));

    int connfd = sbuf_remove(&sbuf);
    doit(connfd);
    Close(connfd);

    // service ends and release lock
    // so thread can be kill at this time
    V(&(threads[idx].mutex));
  }
}

void create_threads(int start, int end) {
  int i;
  for (i = start; i < end; i++) {
    // init mutex for every new thread
    Sem_init(&(threads[i].mutex), 0, 1);
    // create thread
    int *arg = (int*)Malloc(sizeof(int));
    *arg = i;
    // pass thread index in array into thread inside
    Pthread_create(&(threads[i].tid), NULL, serve_thread, arg);
  }
}

void *adjust_threads(void *vargp) {
  sbuf_t *sp = &sbuf;

  while (1) {
    // if sbuf is full, double threads
    if (sbuf_full(sp)) {
      if (nthreads == THREAD_LIMIT) {
        fprintf(stderr, "too many threads, can't double\n");
        continue;
      }

      // double n
      int dn = 2 * nthreads;
      create_threads(nthreads, dn);
      nthreads = dn;
      continue;
    }

    // half threads
    if (sbuf_empty(sp)) {
      if (nthreads == 1)
        continue;

      // half n
      int hn = nthreads / 2;
      /*
       * all server thread are divide to 2 parts
       *
       * keep [0, hn] running
       * kill [hn, nthreads] threads
       *
       * if you want to kill a thread, you must get the lock before it so you
       * won't kill a thread which is offering service.
       */
      int i;
      for (i = hn; i < nthreads; i++) {
        P(&(threads[i].mutex));
        Pthread_cancel(threads[i].tid);
        V(&(threads[i].mutex));
      }
      nthreads = hn;
      continue;
    }
  }
}
