#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sigcb(int signo)
{
    printf("当前进程收到了一个下信号：%d\n",signo);
}

int main()
{  
    signal(SIGINT, sigcb);
    signal(3, sigcb);
    while(1)
    {
        printf("我是有底线的~~~\n");
        sleep(1);
    }

    return 0;
}

