#include<stdio.h>
#include<unistd.h>
//产生僵尸进程
int main(int argc,char *argv[])
{
    pid_t pid = fork();
    if(0 == pid )
    {
        puts("Hi,I am a child process\n");
    }
    else
    {
        printf("Child process ID: %d\n",pid);
        sleep(30);

    }
    if(pid == 0)
    {
        puts("End child process\n");
    }
    else
    {
        puts("End parent process\n");
    }

    return 0;
}


