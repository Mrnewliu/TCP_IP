#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 30

void read_routine(int sock,char* buf);
void write_routine(int sock,char* buf);

int main(int argc,char* argv[])
{
    int sock;
    pid_t pid;
    char buf[BUF_SIZE];
        
    struct sockaddr_in serv_adr;

    if(3 != argc)
    {
        printf("Usage: %s <ip> <port>\n",argv[0]);
        exit(-1);
    }
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sock)
    {
        perror("socket");
        exit(-1);
    }

    bzero(&serv_adr,sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));
    
    if(connect(sock, (struct sockaddr*)&serv_adr,sizeof(serv_adr)) == -1)
    {
        perror("connect");
        exit(-1);
    }

    pid = fork();
    if(0 == pid )
    {
        write_routine(sock, buf);
        //read_routine(sock,buf);
    }
    else
        read_routine( sock, buf);
        //write_routine(sock,buf);
    close(sock);


    return 0;
}




void read_routine(int sock,char* buf)
{
    printf("enter parent process\n");
    while(1)
    {
        int str_len = read(sock, buf,BUF_SIZE);
        if(0 == str_len)
        {
            return;
        }
        buf[str_len] = 0;
        printf("Message from server : %s\n", buf);
    }
}


void write_routine(int sock,char* buf)
{
    printf("enter child process\n");
    while(1)
    {
        fgets(buf, BUF_SIZE, stdin);
        if( !strcmp(buf, "q\n" || !strcmp(buf,"Q\n")))
        {
            shutdown(sock, SHUT_WR);
            return;
        }
        write(sock, buf, strlen(buf));
    }
}



