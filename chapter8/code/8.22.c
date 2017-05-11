/*
 * 8.22.c
 */
#include <stdio.h>
#include "csapp.h"

int mysystem(char* command) {
  pid_t pid;
  int status;

  if ((pid = Fork()) == 0) {
    /* child process */
    char* argv[4] = { "", "-c", command, NULL };
    execve("/bin/sh", argv, environ);
  }

  /* print child pid so we can kill it */
  printf("child pid: %d\n", pid);

  if (Waitpid(pid, &status, 0) > 0) {
    /* exit normally */
    if (WIFEXITED(status))
      return WEXITSTATUS(status);

    /* exit by signal */
    if (WIFSIGNALED(status))
      return WTERMSIG(status);
  }
}

int main(int argc, char* argv[]) {
  int code;

  code = mysystem("./8.test22.exit");
  printf("normally exit, code: %d\n", code); fflush(stdout);

  code = mysystem("./8.test22.sig");
  printf("exit caused by signal, code: %d\n", code); fflush(stdout);
  return 0;
}

