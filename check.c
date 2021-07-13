#include "headers.h"

struct pro
{
	int pid;
	int status;
	char cmd[1024];
};
struct pro backg[1024];
int point = 0, per = 0;

void process(char **a,int x)
{
  pid_t pid,wpid;
  int flag=0,status=0;
  int count = 0, i = 0;

  if (strcmp(a[x - 1], "&") == 0)
  {
	  a[x - 1] = NULL;
	  flag = 1;
  }

  pid=fork();
  if(pid<0)
  {
  	perror("error");
	environ = 1;
	return;
  }
  else if(!pid)
  {
  	if(flag==1 && strcmp(a[0], "vi")==0){exit(EXIT_SUCCESS);}
  	if(execvp(a[0],a)<0)
  	{
		perror("errors");
		exit(EXIT_FAILURE);
	}
  }
  if(flag==0)
 	{
		fore = pid;
		forename = a[0];
		signal(SIGTSTP, zhandler);
	  	wpid = waitpid(pid, &status, WUNTRACED);
	  	bg_arr[pid] = a[0];
	  	if (wpid < 0)
	  	{
		  perror("error2");
		  environ = 1;
		}
		if (WIFEXITED(status))
		{
			const int es = WEXITSTATUS(status);
			if(es > 0)
				environ = 1;
		}
	}
 	else
 	{
		bg_arr[pid] = a[0];
		printf("%s [%d]\n",a[0],pid);
		if(strcmp(a[0], "vi")==0)
			sts[pid] = 2;
		else
		{
			sts[pid] = 1;
		}
		backg[point].pid = pid;
		backg[point].status = 1;
		strcpy(backg[point].cmd, a[0]);
		point++;
	}
}

void jobs_p(char **a, int x)
{
	if (x != 1)
	{
		printf("Invalid syntax");
		environ = 1;
		return;
	}
	int count = 0, i = 0;
	while(i < 100005)
	{
		if (/*bg_arr[i]!=NULL &&*/ sts[i]!=0)
		{
			count++;
			char *hope = (malloc(sizeof(char) * 1005));
			sprintf(hope, "/proc/%d/stat", i);
			FILE *f = fopen(hope, "r");
			if(f==NULL)
			{
				perror("file");
				environ = 1;
				return;
			}
			int p, z=0;
			char s, r[300];
			char *str;
			for (z = 0; z < 3; z++)
			{
				if (z == 0)
					fscanf(f, "%d", &p);
				if (z == 1)
					fscanf(f, "%s", r);
				if (z == 2)
					fscanf(f, " %c", &s);
			}
			if (s == 'R')
				sts[i] = 2;
			if (s == 'S')
				sts[i] = 2;
			if(s!='R' && s!='S')
				sts[i] = 1;
			if(sts[i]==1)
				str = "stopped";
			else
				str = "running";
			printf("[%d] %s\t%s [%d]\n", count, str, bg_arr[i], i);
		}
		i++;
	}
}

void kjob_p(char **a, int x)
{
	int i = 0, count = 0, present = 0;
	int num = atoi(a[1]);
	pid_t pid;
	while (i < 100005)
	{
		if(sts[i]!=0)
		{
			count++;
			if (num == count)
			{
				pid = i;
				present = 1;
				break;
			}
		}
		i++;
	}
	if(!present)
	{
		printf("Invalid job number\n");
		environ = 1;
		return;
	}
	int sig = atoi(a[2]);
	kill(pid, x);
	if(x==9)
	{
		sts[i] = 0;
		bg_arr[i] = NULL;
	}
}

void fg_p(char **a, int x)
{
	int i = 0, count = 1, stk = 0;
	int num = atoi(a[1]);
	while(i < 100005)
	{
		if (sts[i] != 0)
		{
			if(count == num)
			{
				kill(i, SIGCONT);
				waitpid(i, &stk, WUNTRACED);
				if(WIFEXITED(stk))
				{
					bg_arr[i] = NULL;
					sts[i] = 0;
				}
				if (WIFSIGNALED(stk))
				{
					bg_arr[i] = NULL;
					sts[i] = 0;
				}
				break;
			}
			else
				count++;
		}
		i++;
	}
}

void bg_p(char **a, int x)
{
	int i = 0, count = 1;
	int num = atoi(a[1]);
	while (i < 100005)
	{
		if (sts[i] != 0)
		{
			if (count == num)
			{
				kill(i, SIGCONT);
				sts[i] = 2;
				break;
			}
			else
				count++;
		}
		i++;
	}
}

void quit()
{
	/*for(int i=0;i<point;i++)
		if(backg[i].pid>0){kill(backg[i].pid,9);}*/
	int i = 0, count = 0;
	while (i < 100005)
	{
		if (sts[i] != 0)
		{
			count++;
			sts[i] = 0;
			//bg_arr[i] = NULL;
			kill(i, 9);
		}
		i++;
	}
}


void check(char **a, int x)
{
	int count = 0, pip = 0, red = 0, i = 0;
	//printf("h1\n");
	while (a[i] != NULL)
	{
		if (strcmp(a[i], "<") == 0 || strcmp(a[i], ">") == 0)
		{
			red = 1;
			break;
		}
		i++;
	}

	i = 0;
	while (a[i] != NULL)
	{
		if (strcmp(a[i], "|")==0)
		{
			pip = 1;
			break;
		}
		i++;
	}

	if (pip)
	{
		pipe_exec(a);
		return;
	}

	if (red)
	{
		inred(a);
		return;
	}
  if(strcmp(a[0], "echo")==0)
  	echo_p(a,x);
  else if(strcmp(a[0], "pwd")==0)
  	pwd_p(a);
  else if(strcmp(a[0], "cd")==0)
  	cd_p(a,x);
  else if(strcmp(a[0], "ls")==0)
  	ls_p(a,x);
  else if(strcmp(a[0], "pinfo")==0)
  	pinfo_p(a,x);
  else if (strcmp(a[0], "setenv") == 0)
	setenv_p(a, x);
  else if (strcmp(a[0], "unsetenv") == 0)
	unsetenv_p(a, x);
  else if (strcmp(a[0], "jobs") == 0)
	jobs_p(a, x);
  else if (strcmp(a[0], "kjob") == 0)
	  kjob_p(a, x);
  else if (strcmp(a[0], "fg") == 0)
	  fg_p(a, x);
  else if (strcmp(a[0], "bg") == 0)
	  bg_p(a, x);
  else if (strcmp(a[0], "quit") == 0)
	exit(0);
  else if(strcmp(a[0], "overkill")==0)
  {quit(a,x);}
  else process(a,x);
}
