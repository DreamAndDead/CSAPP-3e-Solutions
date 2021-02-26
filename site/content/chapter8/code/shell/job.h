/*
 * job.h
 */
#include "../csapp.h"

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

/*
 * only one process can working on front end
 * and it blocks shell REPL loop unless this process ends.
 *
 * fg pid record the pid of process working on front
 */
// is pid working on front ?
int is_fg_pid(pid_t pid);
// get fg pid
pid_t get_fg_pid();
// set fg pid
void set_fg_pid(pid_t pid);

void init_jobs();
void print_jobs();

int new_job(pid_t pid, char* cmdline, int fg);
void del_job_by_pid(pid_t pid);

JobPtr find_job_by_pid(pid_t pid);
JobPtr find_job_by_jid(Jid jid);
void set_job_status(JobPtr jp, enum JobStatus status);

void test_job(void);


/* signal handler for CHILD, INT, STOP, core of whole shell program */
void sigchild_handler(int sig);
void sigint_handler(int sig);
void sigstop_handler(int sig);

