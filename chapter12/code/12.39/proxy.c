/*
 * proxy.c
 *
 * visited url log to file log.list
 * block url base on entry from file block.list
 */
#include <stdio.h>
#include "../csapp.h"

// block.list limit entry num
#define MAXENTRY 100

int separate_uri(char *uri, char *host, char *port, char *path);
void parse_block_file(char *filename, char list[MAXENTRY][MAXLINE], int limit);
int blocked_uri(char *uri, char list[MAXENTRY][MAXLINE]);

int main(int argc, char **argv) {
  int i, listenfd, connfd;
  int clientfd;

  socklen_t clientlen;
  struct sockaddr_storage clientaddr;

  rio_t client_rio, server_rio;
  char c_buf[MAXLINE], s_buf[MAXLINE];
  ssize_t sn, cn;

  char method[MAXLINE], uri[MAXLINE], version[MAXLINE];
  char host[MAXLINE], port[MAXLINE], path[MAXLINE];

  char block_list[MAXENTRY][MAXLINE];
  int logfd;
  char log_buf[MAXLINE];

  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    fprintf(stderr, "use default port 5000\n");
    listenfd = Open_listenfd("5000");
  } else {
    listenfd = Open_listenfd(argv[1]);
  }

  logfd = Open("log.list", O_WRONLY | O_APPEND, 0);

  memset(block_list, '\0', MAXLINE * MAXENTRY);
  parse_block_file("block.list", block_list, MAXENTRY);

  while (1) {
    // wait for connection as a server
    clientlen = sizeof(struct sockaddr_storage);
    connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);
    Rio_readinitb(&server_rio, connfd);

    /*
     * if uri is full path url like http://localhost:8000/server.c
     * remove host part http://localhost:8000
     * only pass /server.c to server
     */
    // parse HTTP request first line
    if (!Rio_readlineb(&server_rio, s_buf, MAXLINE)) {
      Close(connfd);
      continue;
    }
    sscanf(s_buf, "%s %s %s", method, uri, version);
    // if uri is blocked?
    if (blocked_uri(uri, block_list)) {
      printf("%s is blocked\n", uri);
      Close(connfd);
      continue;
    }
    // log visit
    sprintf(log_buf, "visit url: %s\n", uri);
    Write(logfd, log_buf, strlen(log_buf));

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
    Rio_readinitb(&client_rio, clientfd);

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
      sn = Rio_readlineb(&server_rio, s_buf, MAXLINE);
      printf("%s", s_buf);
      Rio_writen(clientfd, s_buf, sn);
    } while(strcmp(s_buf, "\r\n"));

    /*
     *  server  -->  proxy  -->  browser
     *
     *  server send response back
     */
    while ((cn = Rio_readlineb(&client_rio, c_buf, MAXLINE)) != 0)
      Rio_writen(connfd, c_buf, cn);

    Close(connfd);
    Close(clientfd);
  }

  Close(logfd);
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

/*
 * read block file, parse all the entries and save into list
 * entries count no more than limit
 */
void parse_block_file(char *filename, char list[MAXENTRY][MAXLINE], int limit) {
  int blockfd;
  char block_buf[MAXLINE];
  rio_t block_rio;
  ssize_t block_n;

  blockfd = Open(filename, O_RDONLY, 0);
  Rio_readinitb(&block_rio, blockfd);

  memset(block_buf, '\0', MAXLINE);
  int num = 0;
  while ((block_n = Rio_readlineb(&block_rio, block_buf, MAXLINE)) != 0) {
    // exceed limit
    if (num == limit)
      break;

    // right entry
    if (strncmp(block_buf, "http://", 7) == 0) {
      strcpy(list[num], block_buf);
      num++;
    }

    // comment or not right format entry
    // do nothing
  }

  Close(blockfd);
}

/*
 * if uri is in list, return true
 * if not, return false
 */
int blocked_uri(char *uri, char list[MAXENTRY][MAXLINE]) {
  int i;
  for (i = 0; list[i][0] != '\0'; i++)
    if (strncmp(uri, list[i], strlen(uri)) == 0)
      return 1;

  return 0;
}
