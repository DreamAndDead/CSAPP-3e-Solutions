/*
 * main.c
 */
#include <stdio.h>
#include "../csapp.h"
#include "echoservers.h"

int main(int argc, char **argv)
{
  int listenfd, connfd;
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;
  static pool pool;

  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    fprintf(stderr, "use default port 5000\n");
    listenfd = Open_listenfd("5000");
  } else {
    listenfd = Open_listenfd(argv[1]);
  }

  init_pool(listenfd, &pool); //line:conc:echoservers:initpool

  while (1) {
    /* Wait for listening/connected descriptor(s) to become ready */
    pool.ready_set = pool.read_set;
    pool.nready = Select(pool.maxfd+1, &pool.ready_set, NULL, NULL, NULL);

    /* If listening descriptor ready, add new client to pool */
    if (FD_ISSET(listenfd, &pool.ready_set)) { //line:conc:echoservers:listenfdready
      clientlen = sizeof(struct sockaddr_storage);
      connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen); //line:conc:echoservers:accept
      add_client(connfd, &pool); //line:conc:echoservers:addclient
    }

    /* Echo a text line from each ready connected descriptor */
    check_clients(&pool); //line:conc:echoservers:checkclients
  }
}

