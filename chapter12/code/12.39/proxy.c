/*
 * proxy.c
 */
#include <stdio.h>
#include "../csapp.h"

int separate_uri(char *uri, char *host, char *port, char *path);

int main(int argc, char **argv) {
  int i, listenfd, connfd;
  int clientfd;

  socklen_t clientlen;
  struct sockaddr_storage clientaddr;

  rio_t c_rio, s_rio;
  char c_buf[MAXLINE], s_buf[MAXLINE];
  ssize_t sn, cn;

  char method[MAXLINE], uri[MAXLINE], version[MAXLINE];
  char host[MAXLINE], port[MAXLINE], path[MAXLINE];

  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    fprintf(stderr, "use default port 5000\n");
    listenfd = Open_listenfd("5000");
  } else {
    listenfd = Open_listenfd(argv[1]);
  }

  while (1) {
    // wait for connection as a server
    clientlen = sizeof(struct sockaddr_storage);
    connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);
    Rio_readinitb(&s_rio, connfd);

    /*
     * if uri is full path url like http://localhost:8000/server.c
     * remove host part http://localhost:8000
     * only pass /server.c to server
     */
    // parse HTTP request first line
    if (!Rio_readlineb(&s_rio, s_buf, MAXLINE)) {
      Close(connfd);
      continue;
    }
    sscanf(s_buf, "%s %s %s", method, uri, version);
    memset(host, '\0', MAXLINE);
    memset(port, '\0', MAXLINE);
    memset(path, '\0', MAXLINE);

    int res;
    if ((res = separate_uri(uri, host, port, path)) == -1) {
      fprintf(stderr, "not http protocol\n");
      Close(connfd);
      continue;
    } else if (res == 0) {
      fprintf(stderr, "not a abslute request path\n");
      Close(connfd);
      continue;
    }

    // connect server as a client
    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&c_rio, clientfd);

    /*
     *  browser  -->  proxy  -->  server
     *
     *  send requests
     */
    // write first request line
    sprintf(s_buf, "%s %s %s\n", method, path, version);
    Rio_writen(clientfd, s_buf, strlen(s_buf));
    printf("%s", s_buf);
    do {
      // pass next http requests
      sn = Rio_readlineb(&s_rio, s_buf, MAXLINE);
      printf("%s", s_buf);
      Rio_writen(clientfd, s_buf, sn);
    } while(strcmp(s_buf, "\r\n"));

    /*
     *  server  -->  proxy  -->  browser
     *
     *  server send response back
     */
    while ((cn = Rio_readlineb(&c_rio, c_buf, MAXLINE)) != 0)
      Rio_writen(connfd, c_buf, cn);

    Close(connfd);
    Close(clientfd);
  }
}

/*
 * if uri is abslute path url like
 *   http://localhost:8888/something
 *   or
 *   http://localhost/something (port default is 80)
 * separate into three part and return 1
 *
 * if uri is relative path like /something
 * do nothing and return 0
 *
 * if uri is abslute path and not http protocal like https/ftp/etc
 * do nothing, return -1, it's error
 */
int separate_uri(char *uri, char *host, char *port, char *path) {
  // relative path
  if (uri[0] == '/')
    return 0;

  // abslute path
  char *prefix = "http://";
  int prelen = strlen(prefix);
  // if not http protocal, error
  if (strncmp(uri, prefix, prelen) != 0)
    return -1;

  char *start, *end;
  start = uri + prelen;
  end = start;

  // copy host
  while (*end != ':' && *end != '/') {
    end++;
  }
  strncpy(host, start, end-start);

  // port is provided
  if (*end == ':') {
    // skip ':'
    ++end;
    start = end;
    // copy port
    while (*end != '/')
      end++;
    strncpy(port, start, end-start);
  } else {
    // port is not provided, defualt 80
    strncpy(port, "80", 2);
  }

  // copy path
  strcpy(path, end);
}
