#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 30

void read_childproc(int sig)
{
    pid_t pid;
    int status;
    pid = waitpid(-1, &status, WNOHANG);
    printf("remove proc id :%d\n",pid);


}

int main(int argc,char* argv[])
{
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_adr,clnt_adr;
    int fds[2];
    
    pid_t pid;
    struct sigaction act;
    socklen_t adr_sz;
    int str_len,state;
    char buf[BUF_SIZE];
    if(2 != argc )
    {
        printf("Usage:%s <port>\n",argv[0]);
        exit(-1);
    }

    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    state = sigaction(SIGCHLD,&act, 0);

    serv_sock = socket(AF_INET, SOCK_STREAM , 0);
    if(serv_sock == -1)
    {
        perror("socket");
        exit(-1);
    }
    
    bzero(&serv_adr,sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr)) == -1)
    {
        perror("bind");
        exit(-1);
    }
    if(listen(serv_sock,5) == -1)
    {
        perror("listen");
        exit(-1);
    }
    
    pipe(fds);
    pid = fork();
    if(0== pid)
    {
        FILE* fp = fopen("echomsg.txt","wt");
        char msgbuf[BUF_SIZE];
        int i,len;
        for(i=0;i<10;i++)
        {
            len = read(fds[0],msgbuf,BUF_SIZE);
            fwrite((void*)msgbuf,1,len, fp);

            

        }
        fclose(fp);
        return 0;
    }

    while(1)
    {
        adr_sz = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_adr,&adr_sz);
        if( -1 == clnt_sock)
        {
            continue;
        }
        else
            puts("new client connectd....");

        pid = fork();
        if(pid == 0)
        {
            close(serv_sock);
            while((str_len = read(clnt_sock,buf,BUF_SIZE)) != 0)
            {
                write(clnt_sock,buf,str_len);
                write(fds[1],buf,str_len);
            }
            close(clnt_sock);
            puts("client disconnected...");
            return 0;
        }

        else
            close(clnt_sock);



    }
    
    close(serv_sock);

    return 0;
}






