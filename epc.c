#include"headers.h"

void echo_p(char **a,int x)
{
	if (a[1][0] == '$')
	{
		char out[1005];
		int outlen = strlen(a[1]);
		for (int i = 1; i < outlen;i++)
		{
			out[i - 1] = a[1][i];
		}
		out[outlen] = '\0';
		if (getenv(out) == NULL)
		{
			perror("error:");
			return;
		}
		printf("%s\n", getenv(out));
		return;
	}
  	for(int i=1;;i++)
  	{
  	  if(a[i]==NULL)break;
  	  printf("%s ",a[i]);
  	}
  	printf("\n");
}

void pwd_p()
{
  char *curr_dir=(char*)malloc(1024);
  if(getcwd(curr_dir,1024)!=NULL)
  printf("%s\n",curr_dir);
  else 
  {
    perror("pwd");
	environ = 1;
  }
  free(curr_dir);
}

void cd_p(char**a,int x)
{
	if(a[1]==NULL)
	{
		a[1] = (char *)malloc(2 * sizeof(char));
		a[1][0] = '~';
		a[1][1] = '\0';
		return cd_p(a, x + 1);
	}
	else if(strcmp(a[1],"~")==0 || strcmp(a[1],"~/")==0)
	{
		char *cop = (char *)malloc(1024);
		getcwd(cop, 1024);
		int q = chdir(getenv("PWD"));
		if(q<0)
		{
			environ = 1;
			perror("cd");
		}
		else
		{
			strcpy(c_dir, cop);
			int len=strlen(c_dir);
			c_dir[len] = '\0';
		}
		
	}
	else if(strcmp(a[1],"-")==0)
	{
		strcpy(a[1], c_dir);
		printf("%s\n", a[1]);
		return cd_p(a, x);
	}
	else
	{
		char *cop = (char *)malloc(1024);
		getcwd(cop, 1024);
		int q=chdir(a[1]);
		if(q<0)
		{
			environ = 1;
			perror("cd");
		}
		else
		{
			strcpy(c_dir, cop);
			int len = strlen(c_dir);
			c_dir[len] = '\0';
		}
	}
}

void pinfo_p(char **a,int x)
{
	int curr_pid;
	if(x==1)
	{
		curr_pid=getpid();
		pinfo_e(curr_pid);
	}
	for(int i=1;i<x;i++)
	{
		curr_pid=atoi(a[i]);
		pinfo_e(curr_pid);	
	}
}

void setenv_p(char **a, int x)
{
	if (a[1] == NULL || (a[2] != NULL && a[3] != NULL) || x > 3)
	{
		printf("Incorrect syntax\n");
		environ = 1;
		return;
	}
	int checker = 0;
	if (x == 3)
		checker = setenv(a[1], a[2], 1);
	else
	{
		checker = setenv(a[1], "", 1);
	}
	if (checker < 0)
	{
		environ = 1;
		perror("setenv");
	}
}

void unsetenv_p(char **a, int x)
{
	if (a[1] == NULL)
	{
		printf("Incorrect syntax");
		environ = 1;
		return;
	}
	if (unsetenv(a[1]) < 0)
		{
			perror("unsetenv");
			environ = 1;
		}
}

void zhandler(int signum)
{
	environ = 1;
	sts[fore] = 1;
	kill(fore, SIGTSTP);
	printf("\nProcess %s with pid %d is stopped\n", forename, fore);
	fflush(stdout);
	return;
}

void ctrlC(int signum)
{
	fflush(stdout);
}

void ctrlZ(int signum)
{
	return;
}