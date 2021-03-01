/*
 * echoservers.c - A concurrent echo server based on select
 */
#include "../csapp.h"
#include "echoservers.h"
#include "tiny.h"

static int byte_cnt = 0; /* Counts total bytes received by server */

void init_pool(int listenfd, pool *p)
{
  /* Initially, there are no connected descriptors */
  int i;
  p->maxi = -1;                   //line:conc:echoservers:beginempty
  for (i=0; i< FD_SETSIZE; i++)
    p->clientfd[i] = -1;        //line:conc:echoservers:endempty

  /* Initially, listenfd is only member of select read set */
  p->maxfd = listenfd;            //line:conc:echoservers:begininit
  FD_ZERO(&p->read_set);
  FD_SET(listenfd, &p->read_set); //line:conc:echoservers:endinit
}

void add_client(int connfd, pool *p)
{
  int i;
  p->nready--;
  for (i = 0; i < FD_SETSIZE; i++)  /* Find an available slot */
    if (p->clientfd[i] < 0) {
      /* Add connected descriptor to the pool */
      p->clientfd[i] = connfd;                 //line:conc:echoservers:beginaddclient
      Rio_readinitb(&p->clientrio[i], connfd); //line:conc:echoservers:endaddclient

      /* Add the descriptor to descriptor set */
      FD_SET(connfd, &p->read_set); //line:conc:echoservers:addconnfd

      /* Update max descriptor and pool highwater mark */
      if (connfd > p->maxfd) //line:conc:echoservers:beginmaxfd
        p->maxfd = connfd; //line:conc:echoservers:endmaxfd
      if (i > p->maxi)       //line:conc:echoservers:beginmaxi
        p->maxi = i;       //line:conc:echoservers:endmaxi
      break;
    }
  if (i == FD_SETSIZE) /* Couldn't find an empty slot */
    app_error("add_client error: Too many clients");
}

void check_clients(pool *p)
{
  int i, connfd, n;
  char buf[MAXLINE];
  rio_t rio;

  for (i = 0; (i <= p->maxi) && (p->nready > 0); i++) {
    connfd = p->clientfd[i];
    rio = p->clientrio[i];

    /* If the descriptor is ready, echo a text line from it */
    if ((connfd > 0) && (FD_ISSET(connfd, &p->ready_set))) {
      p->nready--;

      doit(connfd);
      Close(connfd);
      FD_CLR(connfd, &p->read_set); //line:conc:echoservers:beginremove
      p->clientfd[i] = -1;          //line:conc:echoservers:endremove
    }
  }
}

