#include "headers.h"

void pinfo_e(int curr_pid)
{
	char file1[128];
	sprintf(file1,"/proc/%d/stat",curr_pid);
	int fd=open(file1,O_RDONLY);
	if(fd<0){perror("pinfo");return;}
	char buf[512];
	if(read(fd,buf,512)<0)
	{
		perror("pinfo");
		environ = 1;
		return;
	}
	char *ptr;
	int k=0,i=0;
	char *pos[100];
	ptr=strtok(buf," ");
	while(ptr!=NULL)
	{
		if(k==0||k==2||k==22)
		{
			pos[i]=malloc(100*sizeof(char));
			strcpy(pos[i++],ptr);
		}
		k++;
		ptr=strtok(NULL," ");
	}
	printf("pid- %s\n",pos[0]);
	printf("Process status- %s\n",pos[1]);
	printf("Memory- %s {Virtual Memory}\n",pos[2]);
	char file2[128];
	sprintf(file2,"/proc/%d/exe",curr_pid);
	char dest[128];
	if(readlink(file2,dest,128)==-1)
		perror("pinfo");
	else {printf("Executable path- ");prin(dest);}
	
}

void prin(char *dest)
{
	char* home=getenv("PWD");
	int p=strlen(home);
	int q=strlen(dest);
	
	if(p==q)
	{
		printf("~");
	}
	else
	{
		int i;
		printf("~");
		for(i=p;i<q;i++)
			printf("%c",dest[i]);
	}
	printf("\n");
}
