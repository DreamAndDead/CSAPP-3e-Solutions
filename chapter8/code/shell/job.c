/*
 * job.c
 */
#include <stdio.h>
#include <assert.h>
#include "job.h"
#include "../csapp.h"

static volatile sig_atomic_t fg_pid;
static Job jobs[MAXJOBS];

int is_fg_pid(pid_t pid) {
  return fg_pid == pid;
}
pid_t get_fg_pid() {
  return fg_pid;
}
void set_fg_pid(pid_t pid) {
  fg_pid = pid;
}

/* SIGCONT signal */
void sigchild_handler(int sig) {
  int old_errno = errno;
  int status;
  pid_t pid;

  sigset_t mask_all, prev_all;
  Sigfillset(&mask_all);

  /* exit or be stopped or continue */
  while ((pid = waitpid(-1, &status, WNOHANG|WUNTRACED|WCONTINUED)) > 0) {
    /* exit normally */
    if (WIFEXITED(status) || WIFSIGNALED(status)) {
      if (is_fg_pid(pid)) {
        set_fg_pid(0);
      } else {
        Sio_puts("pid "); Sio_putl(pid); Sio_puts(" terminates\n");
      }
      Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
      del_job_by_pid(pid);
      Sigprocmask(SIG_SETMASK, &prev_all, NULL);
    }

    /* be stopped */
    if (WIFSTOPPED(status)) {
      if (is_fg_pid(pid)) {
        set_fg_pid(0);
      }
      // set pid status stopped
      Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
      JobPtr jp = find_job_by_pid(pid);
      set_job_status(jp, Stopped);
      Sigprocmask(SIG_SETMASK, &prev_all, NULL);

      Sio_puts("pid "); Sio_putl(pid); Sio_puts(" be stopped\n");
    }

    /* continue */
    if(WIFCONTINUED(status)) {
      set_fg_pid(pid);
      // set pid status running
      Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
      JobPtr jp = find_job_by_pid(pid);
      set_job_status(jp, Running);
      Sigprocmask(SIG_SETMASK, &prev_all, NULL);

      Sio_puts("pid "); Sio_putl(pid); Sio_puts(" continue\n");
    }
  }

  errno = old_errno;
}

void sigint_handler(int sig) {
  /* when fg_pid == 0, stop shell itself, it'll be a dead loop */
  if (is_fg_pid(0)) {
    Signal(SIGINT, SIG_DFL);
    Kill(getpid(), SIGINT);
  } else {
    Kill(get_fg_pid(), SIGINT);
  }
}

void sigstop_handler(int sig) {
  /* same like int handler */
  if (is_fg_pid(0)) {
    Signal(SIGTSTP, SIG_DFL);
    Kill(getpid(), SIGTSTP);
  } else {
    Kill(get_fg_pid(), SIGTSTP);
  }
}

JobPtr find_job_by_jid(Jid jid) {
  return &(jobs[jid]);
}

JobPtr find_job_by_pid(pid_t pid) {
  for (int i = 0; i < MAXJOBS; i++) {
    Job j = jobs[i];
    if (j.using && j.pid == pid) {
      return &(jobs[i]);
    }
  }
  /* no such job */
  return NULL;
}

void set_job_status(JobPtr jp, enum JobStatus status) {
  if (jp)
    jp->status = status;
}


// seek a spare place for new job
static int find_spare_jid() {
  Jid jid = -1;
  for (int i = 0; i < MAXJOBS; i++) {
    if (jobs[i].using == 0) {
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
  jobs[jid].jid = jid;
  jobs[jid].pid = pid;
  jobs[jid].status = Running;
  strcpy(jobs[jid].cmdline, cmdline);
  jobs[jid].using = 1;

  return jid;
}

void del_job_by_pid(pid_t pid) {
  // search job whose pid is pid
  for (int i = 0; i < MAXJOBS; i++) {
    if (jobs[i].using && jobs[i].pid == pid) {
      // delete job
      jobs[i].using = 0;
    }
  }
}

void print_jobs() {
  for (int i = 0; i < MAXJOBS; i++) {
    Job j = jobs[i];
    if (j.using) {
      printf("[%d] %d %s \t %s\n", j.jid, j.pid,
          j.status == Running ? "Running" : "Stopped", j.cmdline);
    }
  }
}

void init_jobs() {
  memset(jobs, 0, sizeof(jobs));
}

void test_job() {

}
