#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>

void error_handling(char *message);

int main(int argc,char* argv[])
{
    int sock;
    struct sockaddr_in sock_addr;
    char message[30];
    int str_len;
    
    if( argc != 3)
    {
        printf("Usage: %s <port>\n",argv[0]);
        exit(-1);
    }


    sock = socket(AF_INET,SOCK_STREAM,0);
    if( sock == -1)
    {
        error_handling("socket() error");

    }
      
    memset(&sock_addr,0,sizeof(sock_addr));

    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = inet_addr(argv[1]);
    sock_addr.sin_port = htons(atoi(argv[2]));

    if( connect(sock, (struct sockaddr*)&sock_addr,sizeof(struct sockaddr))== -1)
    {
        perror("connect");
        error_handling("connect() error");
    }
    str_len = read(sock,message,sizeof(message)-1);
    
    printf("Message from server: %s\n",message);
    
    close(sock);
        
    return 0;
}



void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}


