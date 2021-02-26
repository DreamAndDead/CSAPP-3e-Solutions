/*
 * main.c
 */
#include <stdio.h>
#include "../csapp.h"
#include "shell.h"
#include "job.h"

int main() {
  // some test for furture
  test_shell();
  test_job();

  init_jobs();

  /* set signal handlers */
  if (Signal(SIGCHLD, sigchild_handler) == SIG_ERR)
    unix_error("signal child handler error");
  if (Signal(SIGINT, sigint_handler) == SIG_ERR)
    unix_error("signal int handler error");
  if (Signal(SIGTSTP, sigstop_handler) == SIG_ERR)
    unix_error("signal stop handler error");

  char cmdline[MAXLINE];
  while (1) {
    printf("> ");
    Fgets(cmdline, MAXLINE, stdin);
    if (feof(stdin))
      exit(0);

    eval(cmdline);
  }
}

