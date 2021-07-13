#include"headers.h"

void inred(char **a)
{
    int f_1 = 0, f_2 = 0, f_3 = 0, i = 0;
    while(a[i]!=NULL)
        if(strcmp(a[i++], "<")==0)
            f_1 = 1;
    i = 0;
    while (a[i] != NULL)
        if (strcmp(a[i++], ">") == 0)
            f_2 = 1;
    i = 0;
    while (a[i] != NULL)
        if (strcmp(a[i++], ">>") == 0)
            f_3 = 1;


    char in[1000], out[1000];

    int mx = 1000000;
    if(f_1==1)
    {
        //printf("hello\n");
        i = 0;
        while(a[i]!=NULL)
        {
            if(strcmp(a[i],"<")==0)
            {
                if(i-1<mx)
                    mx = i - 1;
                strcpy(in, a[i + 1]);
            }
            i++;
        }
    }

    if(f_2==1 || f_3==1)
    {
        i = 0;
        while (a[i] != NULL)
        {
            if (strcmp(a[i], ">") == 0 || strcmp(a[i], ">>") == 0)
            {
                if (i - 1 < mx)
                    mx = i - 1;
                strcpy(out, a[i + 1]);
            }
            i++;
        }
    }

    a[mx + 1] = NULL;
    int original_in, original_out, filed[2];

    if(f_1==1)
    {
        //printf("hi\n");
        struct stat fl;
        if(stat(in, &fl)==-1)
            perror("stat");
        original_in = dup(0);
        filed[0] = open(in, O_RDONLY, 0644);
        if(dup2(filed[0], 0)==-1)
        {
            perror("dup2");
            //printf("hi\n");
            environ = 1;
            return;
        }
    }

    if(f_2==1 || f_3==1)
    {
        original_out = dup(1);
        if(f_2==1)
            filed[1] = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else
            filed[1] = open(out, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if(dup2(filed[1], 1)==-1)
        {
            perror("dup2");
            //printf("his\n");
            environ = 1;
            return;
        }
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
        if(execvp(a[0],a)==-1)
        {
            perror("execvp");
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
        dup2(original_in, 0);
        dup2(original_out, 1);
    }
}