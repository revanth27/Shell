#include "headers.h"

void pipe_exec(char **a)
{
    int i = 0, count = 0, num = 0, j = 0, flag = 0;
    int x = i, fild;
    i = 0;
    char *hope[1005];
    while(1)
    {
        if(a[i]==NULL || flag==1)
            break;
        int s = 0;
        while(1)
        {
            if(a[j]==NULL)
            {
                flag = 1;
                break;
            }
            if(strcmp(a[j],"|")!=0)
            {
                hope[s] = a[j];
                s++;
            }
            else
                break;
            j++;
        }
        count++;
        j++;
        hope[s] = NULL;
        int or_in, or_out, fd[2];
        if(count==1)
        {
            if(pipe(fd)==-1)
            {
                perror("pipe");
                environ = 1;
                return;
            }
            int z = 0;
            char infile[1005];
            while(hope[z]!=NULL)
            {
                if(strcmp(a[z],"<")==0)
                {
                    hope[z] = NULL;
                    strcpy(infile, hope[z + 1]);
                    or_in = dup(0);
                    fild = open(infile, O_RDONLY, 0644);
                    dup2(fild, 0);
                }
                z++;
            }
            or_out = dup(1);
            dup2(fd[1], 1);
            close(fd[1]);
        }
        else if(flag==0)
        {
            or_in = dup(0);
            dup2(fd[0], 0);
            if (pipe(fd) == -1)
            {
                perror("pipe");
                environ = 1;
                return;
            }
            or_out = dup(1);
            dup2(fd[1], 1);
            close(fd[1]);
        }
        else 
        {
            int z = 0;
            char outfile[1005];
            while(hope[z]!=NULL)
            {
                if(strcmp(hope[z], ">")==0)
                {
                    hope[z] = NULL;
                    strcpy(outfile, hope[z + 1]);
                    or_out = dup(1);
                    fild = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(fild, 1);
                    close(fild);
                }
                else if(strcmp(hope[z],">>")==0)
                {
                    hope[z] = NULL;
                    strcpy(outfile, hope[z + 1]);
                    or_out = dup(1);
                    fild = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    dup2(fild, 1);
                    close(fild);
                }
                z++;
            }
            or_in = dup(0);
            dup2(fd[0], 0);
            close(fd[0]);
        }
    
        pid_t pid;
        pid = fork();

        if(pid<0)
        {
            perror("fork");
            environ = 1;
            return;
        }
        else if(pid==0)
        {
            if(execvp(hope[0],hope)==-1)
            {
                perror("error");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            int stak;
            wait(&stak);
            if (WIFEXITED(stak))
            {
                const int es = WEXITSTATUS(stak);
                if (es > 0)
                    environ = 1;
            }
            dup2(or_in, 0);
            dup2(or_out, 1);
        }
    }
}