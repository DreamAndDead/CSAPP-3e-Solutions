#include "../csapp.h"
#include "shell.h"
#include "job.h"

void eval(char *cmdline)
{
  char *argv[MAXARGS]; /* Argument list execve() */
  char buf[MAXLINE];   /* Holds modified command line */
  int bg;              /* Should the job run in bg or fg? */
  pid_t pid;           /* Process id */

  strcpy(buf, cmdline);
  bg = parse_line(buf, argv);
  if (argv[0] == NULL)
    return;   /* Ignore empty lines */

  if (!builtin_command(argv)) {
    sigset_t mask_one, prev_one;
    Sigemptyset(&mask_one);
    Sigaddset(&mask_one, SIGCHLD);

    /* block signal child */
    Sigprocmask(SIG_BLOCK, &mask_one, &prev_one);
    if ((pid = Fork()) == 0) {
      /* unblock in child process */
      Sigprocmask(SIG_SETMASK, &prev_one, NULL);
      printf("child process pid: %d\n", getpid());

      Setpgid(0, 0);
      if (execve(argv[0], argv, environ) < 0) {
        printf("%s: Command not found.\n", argv[0]);
        exit(0);
      }
    }

    sigset_t mask_all, prev_all;
    Sigfillset(&mask_all);
    // save job info
    Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
    Jid new_jid = new_job(pid, cmdline, !bg);
    Sigprocmask(SIG_SETMASK, &prev_all, NULL);

    if (!bg) {
      fg_pid = pid;
      while(fg_pid)
        sigsuspend(&prev_one);
    }
    else
      printf("[%d] %d %s \t %s", new_jid, pid, "Running", cmdline);

    /* unblock child signal */
    Sigprocmask(SIG_SETMASK, &prev_one, NULL);
  }
  return;
}

/*
 * If first arg is a builtin command, run it and return true;
 * else return false.
 */
int builtin_command(char **argv)
{
  if (!strcmp(argv[0], "quit")) /* quit command */
    exit(0);
  if (!strcmp(argv[0], "&"))    /* Ignore singleton & */
    return 1;
  if (!strcmp(argv[0], "jobs")) {
    print_jobs();
    return 1;
  }
  // fg command
  if (!strcmp(argv[0], "fg")) {
    char* id = argv[1];

    if (id == NULL) {
      printf("fg need params\n");
      return 1;
    }
    if (id[0] == '%' && id[1] == '\0') {
      printf("fg %% , no jid here");
      return 1;
    }

    sigset_t mask_one, prev_one;
    Sigemptyset(&mask_one);
    Sigaddset(&mask_one, SIGCHLD);
    Sigprocmask(SIG_BLOCK, &mask_one, &prev_one);

    if (id[0] == '%') {
      // CONT by jid
      Jid j = atoi(id+1);
      JobPtr jp = find_job_by_jid(j);
      Kill(jp->pid, SIGCONT);
      fg_pid = jp->pid;
    } else {
      // CONT by pid
      pid_t p = atoi(id);
      Kill(p, SIGCONT);
      fg_pid = p;
    }
    while(fg_pid)
      sigsuspend(&prev_one);

    Sigprocmask(SIG_SETMASK, &prev_one, NULL);

    return 1;
  }

  return 0;                     /* Not a builtin command */
}

/* parse_line - Parse the command line and build the argv array */
int parse_line(char *buf, char **argv)
{
  char *delim;         /* Points to first space delimiter */
  int argc;            /* Number of args */
  int bg;              /* Background job? */

  buf[strlen(buf)-1] = ' ';  /* Replace trailing '\n' with space */
  while (*buf && (*buf == ' ')) /* Ignore leading spaces */
    buf++;

  /* Build the argv list */
  argc = 0;
  while ((delim = strchr(buf, ' '))) {
    argv[argc++] = buf;
    *delim = '\0';
    buf = delim + 1;
    while (*buf && (*buf == ' ')) /* Ignore spaces */
      buf++;
  }
  argv[argc] = NULL;

  if (argc == 0)  /* Ignore blank line */
    return 1;

  /* Should the job run in the background? */
  if ((bg = (*argv[argc-1] == '&')) != 0)
    argv[--argc] = NULL;

  return bg;
}


