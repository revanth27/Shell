#include <sys/types.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<dirent.h>
#include <sys/stat.h>
#include<fcntl.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<signal.h>
#include<errno.h>
extern int errno;


void echo_p(char** a, int x);
void pwd_p();
void cd_p(char** a, int x);
char **in();
void parse_sp(char *input);
char** parse_semi(char* input);
void prompt();
void check(char** a, int x);
void process1(char** a,int x);
void ls_p(char** a, int x);
void ls_0(char *a,int b);
void ls_l(char *a,int b);
void go(char *name, char *a);
void pinfo_e(int curr_pid);
void pinfo_p(char **a,int x);
void prin(char *dest);
void quit();
void handler(int sig, siginfo_t *siginfo, void *context);
void inred(char **a);
void pipe_exec(char **a);
void setenv_p(char **a, int x);
void unsetenv_p(char **a, int x);
void jobs_p(char **a, int x);
void kjob_p(char **a, int x);
void fg_p(char **a, int x);
void bg_p(char **a, int x);
void ctrlZ(int signum);
void ctrlC(int signum);
void zhandler(int signum);

pid_t fore;
char *forename;
char **bg_arr;
int sts[100005];
char *c_dir;
char *current;
int environ;
int track;
