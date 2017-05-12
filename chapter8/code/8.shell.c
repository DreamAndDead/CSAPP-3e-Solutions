/* $begin shellmain */
#include "csapp.h"
#define MAXARGS   128

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);

void del_job_by_pid(pid_t pid);

#define MAXJOBS 128

enum JobStatus { Running, Stopped };

typedef int Jid;

typedef struct {
  Jid jid;
  pid_t pid;
  enum JobStatus status;
  char cmdline[MAXLINE];
  int using;
} Job, *JobPtr; /* single job */

typedef struct {
  int fg_jid; // -1 means none
  Job jobs[MAXJOBS];
} JobPool, *JobPoolPtr; /* job manager */

JobPool job_pool;
JobPoolPtr job_pool_ptr = &job_pool;

volatile sig_atomic_t fg_pid;

void sigchild_handler(int sig) {
  int old_errno = errno;
  pid_t pid;

  sigset_t mask_all, prev_all;
  Sigfillset(&mask_all);

  while ((pid = waitpid(-1, NULL, 0)) > 0) {
    if (pid == fg_pid) {
      fg_pid = 0;
    }
    else {
      Sio_puts("pid "); Sio_putl(pid); Sio_puts(" terminate normally\n");
    }
    Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
    del_job_by_pid(pid);
    Sigprocmask(SIG_SETMASK, &prev_all, NULL);
  }

  errno = old_errno;
}

void sigint_handler(int sig) {

}

int find_spare_jid() {
  Jid jid = -1;
  for (int i = 0; i < MAXJOBS; i++) {
    if (job_pool_ptr->jobs[i].using == 0) {
      jid = i;
      break;
    }
  }
  return jid;
}

int new_job(pid_t pid, char* cmdline, int fg) {
  // find a jid
  Jid jid = find_spare_jid();
  if (jid == -1)
    unix_error("no more jid to use");

  // save process info
  job_pool_ptr->jobs[jid].jid = jid;
  job_pool_ptr->jobs[jid].pid = pid;
  job_pool_ptr->jobs[jid].status = Running;
  strcpy(job_pool_ptr->jobs[jid].cmdline, cmdline);
  job_pool_ptr->jobs[jid].using = 1;
  if (fg)
    job_pool_ptr->fg_jid = jid;

  return jid;
}

void del_job_by_pid(pid_t pid) {
  // search job whose pid is pid
  for (int i = 0; i < MAXJOBS; i++) {
    if (job_pool_ptr->jobs[i].using && job_pool_ptr->jobs[i].pid == pid) {
      // delete job
      job_pool_ptr->jobs[i].using = 0;
      if (i == job_pool_ptr->fg_jid)
        job_pool_ptr->fg_jid = -1;
    }
  }
}

void list_jobs() {
  for (int i = 0; i < MAXJOBS; i++) {
    Job j = job_pool_ptr->jobs[i];
    if (j.using) {
      printf("[%d] %d %s \t %s", j.jid, j.pid,
        j.status == Running ? "Running" : "Stopped", j.cmdline);
    }
  }
}

void initjobs() {
  job_pool_ptr->fg_jid = -1;
  memset(job_pool_ptr->jobs, 0, sizeof(job_pool_ptr->jobs));
}


int main()
{
  initjobs();

  /* signal handlers */
  if (Signal(SIGCHLD, sigchild_handler) == SIG_ERR) {
    unix_error("set signal child error");
  }
  if (Signal(SIGINT, sigint_handler) == SIG_ERR) {
    unix_error("set signal int error");
  }

  char cmdline[MAXLINE]; /* Command line */

  while (1) {
    /* Read */
    printf("$ ");
    Fgets(cmdline, MAXLINE, stdin);
    if (feof(stdin))
      exit(0);

    /* Evaluate */
    eval(cmdline);
  }
}
/* $end shellmain */

/* $begin eval */
/* eval - Evaluate a command line */
void eval(char *cmdline)
{
  char *argv[MAXARGS]; /* Argument list execve() */
  char buf[MAXLINE];   /* Holds modified command line */
  int bg;              /* Should the job run in bg or fg? */
  pid_t pid;           /* Process id */

  strcpy(buf, cmdline);
  bg = parseline(buf, argv);
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

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv)
{
  if (!strcmp(argv[0], "quit")) /* quit command */
    exit(0);
  if (!strcmp(argv[0], "&"))    /* Ignore singleton & */
    return 1;
  if (!strcmp(argv[0], "jobs")) {
    list_jobs();
    return 1;
  }

  return 0;                     /* Not a builtin command */
}
/* $end eval */

/* $begin parseline */
/* parseline - Parse the command line and build the argv array */
int parseline(char *buf, char **argv)
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
/* $end parseline */


