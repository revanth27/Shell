#include"headers.h"

char** parse_semi(char* input)
{
  char **a=malloc(16*sizeof(char*));
	int in_size=1024,x=0;
  const char delim[2]=";";
  char *token;
  
  token=strtok(input, delim);
  while(token!=NULL)
  {
    a[x]=token;
    x++;
    token=strtok(NULL, delim);
  }
  a[x]=token;
  return a;
}

void parse_sp(char* input)
{
  char **a=malloc(16*sizeof(char*));
	int in_size=1024,x=0;
  const char delim[2]=" ";
  char *token;
  
  token=strtok(input, delim);
  while(token!=NULL)
  {
    a[x]=token;
    x++;
    token=strtok(NULL, delim);
  }
  a[x]=token;
  return check(a,x);
}


