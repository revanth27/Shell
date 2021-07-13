#include"headers.h"

void prompt()
{
	if(track)
	{
		if (environ == 1)
			printf(":'(");
		else
			printf(":')");
	}
	track++;
	environ = 0;
	struct utsname user;
	uname(&user);
	char* username=getenv("USER");
	char* hostname=user.nodename;
	
	//if(work==1){quit();back();work=0;}
	
	char set[1024];
	char* home=getenv("PWD");
	char* curr_dir=(char*)malloc(1024);
	getcwd(curr_dir,1024);
	
	int p = strlen(home);
	int q=strlen(curr_dir);
	
	if(p>q){
		sprintf(set,"<%s@%s:%s>",username,hostname,curr_dir);
		printf("%s",set);
	}
	else if(p==q)
	{
		sprintf(set,"<%s@%s:~>",username,hostname);
		printf("%s",set);
	}
	else
	{
		int i;
		sprintf(set,"<%s@%s:~",username,hostname);
		printf("%s",set);
		for(i=p;i<q+1;i++)
			printf("%c",curr_dir[i]);
		printf("%c",'>');
	}

	signal(SIGTSTP, ctrlZ);
	signal(SIGINT, ctrlC);
	int i = 0;

	fore = -1;
	forename=NULL;
	char **a = in();
	for(i=0;;i++)
	{
		int status;
		pid_t pid = waitpid(-1, &status, WNOHANG);
		if (pid > 0 && WIFEXITED(status) > 0)
		{
			printf("Process %s with pid: %d exited normally\n", bg_arr[pid], pid);
			sts[pid] = 0;
			bg_arr[pid] = NULL;
		}
		else if (pid > 0 && WIFSIGNALED(status) == 1)
		{
			printf("Process %s with pid: %d exited abnormally\n", bg_arr[pid], pid);
		}
		if (a[i] == NULL)
			break;
		//back();
		parse_sp(a[i]);
	}
}

