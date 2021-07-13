#include "headers.h"

void ls_0(char* a,int b)
{	
	struct dirent *dirent;
	char shi[1024];
	char* home=getenv("PWD");
	//printf("%s:\n",a);
	if(strcmp(a,"~")==0)strcpy(shi,home);
	else strcpy(shi,a);
	DIR *dir=opendir(shi);
	if(dir==NULL)
	{
		perror("ls");
		environ = 1;
		return;
	}
	while((dirent=readdir(dir))!=NULL)
	{
		if(b==0 && dirent->d_name[0]!='.')printf("%s\n",dirent->d_name);
		else if(b==1)printf("%s\n",dirent->d_name);
	}
	closedir(dir);
}

long int blocks=0;

void ls_l(char *a,int b)
{
	struct dirent *dirent;
	char shi[1024];
	char* home=getenv("PWD");
	//printf("%s:\n",a);
	if(strcmp(a,"~")==0)strcpy(shi,home);
	else strcpy(shi,a);
	DIR *dir=opendir(shi);
	if(dir==NULL)
	{
		perror("ls");
		environ = 1;
		return;
	}
	while((dirent=readdir(dir))!=NULL)
	{
		if(b==0 && dirent->d_name[0]!='.'){go(dirent->d_name,shi);}
		else if(b==1)go(dirent->d_name,shi);
	}
	printf("total %ld\n",blocks/2);
	blocks=0;
	closedir(dir);
}

void go(char *name, char *a)
{
	char path[2048];
	strcpy(path,a);
	int k=strlen(path);
	if(path[k-1]!='/')
		strcat(path,"/");
	strcat(path,name);
	
	struct stat ret;
	if(stat(path,&ret)==-1)
	{
		perror("ls -l");
		environ = 1;
		return;
	}
	
	mode_t bits=ret.st_mode;
	char perm[11];
	
	if(S_ISDIR(bits))perm[0]='d';
	else perm[0]='-';
	
	int user[3]={bits & S_IRUSR,bits & S_IWUSR,bits & S_IXUSR};
	int group[3]={bits & S_IRGRP,bits & S_IWGRP,bits & S_IXGRP};
	int others[3]={bits & S_IROTH,bits & S_IWOTH,bits & S_IXOTH};
	char p[4]={'r','w','x','-'};
	
	for(int i=0;i<3;i++)
	{
		if(user[i])perm[1+i]=p[i];
		else perm[1+i]=p[3];
		if(group[i])perm[4+i]=p[i];
		else perm[4+i]=p[3];
		if(others[i])perm[7+i]=p[i];
		else perm[7+i]=p[3];
	}
	perm[10]='\0';
	printf("%s\t%ld\t",perm,ret.st_nlink);
	printf("%s\t",getpwuid(ret.st_uid)->pw_name);
	printf("%s\t",getgrgid(ret.st_gid)->gr_name);
	printf("%ld\t",ret.st_size);
	blocks+=ret.st_blocks;
	char cur_time[30];
	struct tm *lc;
	time_t t=ret.st_mtime;
	lc=localtime(&t);
	
	strftime(cur_time,sizeof(cur_time),"%h %e %H:%M", lc);
	printf("%s\t",cur_time);
	printf("%s\n",name);
}


