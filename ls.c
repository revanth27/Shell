#include "headers.h"

void ls_p(char** a, int x)
{
	int k=1,f_1=0,f_2=0;
	char* home=getenv("PWD");
	if(x==1){ls_0(".",0);return;}
	if(x==2)
	{
		if(a[1][0]!='-'){
				if(a[1][0]=='~')
					ls_0(home,0);
				else ls_0(a[1],0);
				return;
			}
	}
	int num[x-1];
	num[0]=0;
	for(int i=0;i<x;i++)
	{
		if(x>=2+i && a[1+i][0]=='-')
		{
			if(strcmp(a[1+i],"-l")==0)f_1=1;
			if(strcmp(a[1+i],"-a")==0)f_2=1;
			if(strcmp(a[1+i],"-la")==0||strcmp(a[1+i],"-al")==0){f_1=1;f_2=1;}
			num[k]=i+1;
			k++;
		}
	}
	
	if(k==x){
		if(f_1==1&&f_2==1)
			{ls_l(".",1);}
		else if(f_1==1)
			{ls_l(".",0);}
		else if(f_2==1)
			{ls_0(".",1);}
		else {ls_0(".",0);}
		return;
	}
	
	int count=1;
	for(int i=1;i<x;i++)
	{
		
		if(count<k && i==num[count]){count++;continue;}
		printf("%s:\n",a[i]);
		if(f_1==1&&f_2==1)
			{ls_l(a[i],1);}
		else if(f_1==1)
			{ls_l(a[i],0);}
		else if(f_2==1)
			{ls_0(a[i],1);}
		else {ls_0(a[i],0);}
	}
	printf("\n");
}


