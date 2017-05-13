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

typedef struct {
  int fg_jid; // -1 means none
  Job jobs[MAXJOBS];
} JobPool, *JobPoolPtr; /* job manager */

volatile sig_atomic_t fg_pid;

void del_job_by_pid(pid_t pid);
void sigchild_handler(int sig);
void sigint_handler(int sig);
void sigstop_handler(int sig);
int find_spare_jid();
int new_job(pid_t pid, char* cmdline, int fg);
void del_job_by_pid(pid_t pid);
void print_jobs();
void init_jobs();

JobPtr find_job_by_pid(pid_t pid);
JobPtr find_job_by_jid(Jid jid);
void set_job_status(JobPtr jp, enum JobStatus status);
