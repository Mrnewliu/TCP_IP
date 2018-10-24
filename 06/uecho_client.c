#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 30

int main(int argc,char* argv[])
{
    
    int sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t adr_sz;
    
    struct sockaddr_in serv_adr,from_adr;
    
    if(3 != argc)
    {
        printf("Usage:%s <ip> <port>\n",argv[0]);
        exit(-1);
    }
    
    
    
    sock = socket(AF_INET,SOCK_DGRAM,0);
    if(-1 == sock)
    {
        perror("socket");
        exit(-1);
    }
    
    bzero(&serv_adr,sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port = htons(atoi(argv[2]));
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);

    while(1)
    {
        fputs("Insert message(q to quit): ",stdout);
        fgets(message,sizeof(message),stdin);
        if( !strcmp(message,"q\n") || !strcmp(message,"Q\n"))
            break;
        
        sendto(sock,message,strlen(message),0,(struct sockaddr*)&serv_adr,sizeof(serv_adr));
        adr_sz = sizeof(from_adr);
        memset(message,0,BUF_SIZE);
        str_len = recvfrom(sock,message,BUF_SIZE,0,(struct sockaddr*)&from_adr,&adr_sz);
        message[str_len] = 0;
        printf("Messae from server: %s",message);

    }

    close(sock);
    

    return 0;
}



