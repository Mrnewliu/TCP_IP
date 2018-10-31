#include<stdio.h>
#include<unistd.h>

#define BUF_SIZE 30

int main(int argc,char* argv[])
{
    int fds[2];
    char str1[] = "who are you?";
    char str2[] = "Thank you for your message";
        
    char buf[BUF_SIZE];
    pipe(fds);

    pid_t pid;
    pid = fork();
    if(0 == pid)
    {
        write(fds[1],str1,sizeof(str1) );
//将产生问题
//        sleep(2);
        read(fds[0],buf,BUF_SIZE);
        printf("Child proc output: %s\n", buf);

    }
    else
    {
        //父进程
        read(fds[0],buf,BUF_SIZE);
        printf("Parents proc output: %s\n",buf);
        write(fds[1], str2,sizeof(str2));
        sleep(3);
    }





    return 0;
}



