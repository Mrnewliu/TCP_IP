#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUF_SIZE  30

int main(int argc,char *argv[])
{
    int sock;
    //char message[BUF_SIZE];
    char msg1[] = "Hi!";
    char msg2[] = "I'm another UDP host";
    char msg3[] = "Nice to meet you";
    struct sockaddr_in to_adr;
    socklen_t adr_len;
    if(3 != argc)
    {
        printf("Usage:%s <ip> <port>\n",argv[0]);
        exit(-1);
    }

    
    sock = socket(AF_INET,SOCK_DGRAM,0);
    if(-1 == sock )
    {
        perror("socket");
        exit(-1);
    }

    bzero(&to_adr,sizeof(to_adr));
    to_adr.sin_family = AF_INET;
    to_adr.sin_port = htons(atoi(argv[2]));
    to_adr.sin_addr.s_addr = inet_addr(argv[1]);
    //adr_len = sizeof(to_adr);

    sendto(sock, msg1,sizeof(msg1),0,(struct sockaddr*)&to_adr,sizeof(to_adr));
    sendto(sock, msg2,sizeof(msg2),0,(struct sockaddr*)&to_adr,sizeof(to_adr));
    sendto(sock, msg3,sizeof(msg3),0,(struct sockaddr*)&to_adr,sizeof(to_adr));
    
    close(sock);


    return 0;
}

