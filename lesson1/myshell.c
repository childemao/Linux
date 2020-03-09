#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include<unistd.h>
#include<sys/wait.h>

#define IN 1
#define OUT 0
void ParseArg(char input[],char* output[]);
int Run(char* argv[]);

int main()
{
    char buf[1024] = {0};
    while(1)
    {
        printf("[maoheng@izuf68phfbhbm8bn16zrhrz learn]$");
        fflush(stdout);
        scanf("%[^\n]%*c",buf);

        char *argv[100] = {0};
        ParseArg(buf,argv);

        Run(argv);
    }
    return 0;
}

void ParseArg(char input[],char *output[])
{
    int argc = 0;
    int flag = OUT;
    int i = 0;
    for(i = 0;input[i] != '\0';i++)
    {
        if(!isspace(input[i]) && flag == OUT)
        {
            flag == IN;
            output[argc++] = &input[i];
        }
        else if(isspace(input[i]))
        {
            flag = OUT;
            input[i] = '\0';
        }
    }
    output[argc] = NULL;
}

int Run(char *argv[])
{
    pid_t pid = fork();
    if(pid == 0)
    {
        execvp(argv[0],argv);
        printf("command %s not found\n",argv[0]);
        exit(1);
    }
    int status;
    waitpid(pid,&status,0);
    return 0;
}





