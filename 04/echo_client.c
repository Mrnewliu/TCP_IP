#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>


#define BUF_SIZE 1024



int main(int argc,char* argv[])
{
    int sock;
    char message[BUF_SIZE];
    int str_len;
    struct sockaddr_in serv_adr;

    if(argc != 3)
    {
        printf("Usage:%s <ip> <port>\n",argv[0]);
        exit(-1);
    }
    
    sock = socket(AF_INET,SOCK_STREAM, 0);
    if(-1 == sock)
    {
        perror("socket");
        exit(-1);
    }
    bzero(&serv_adr,sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port = htons(atoi(argv[2]));
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    

    if(connect(sock,(struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
    {
        perror("connect"); 
        exit(-1);
    }
    else
    {
        printf("Connect .....\n");
    }

    while(1)
    {
        fputs("Input message(Q to quit): ",stdout);
        fgets(message,BUF_SIZE,stdin);

        if( !strcmp(message,"q\n")|| !strcmp(message,"Q\n") )
            break;

         write(sock,message,strlen(message));
        str_len = read(sock, message,BUF_SIZE-1);
        message[str_len] = 0;
        printf("Message from server:%s\n",message);

        
    
    }

    close(sock);

    return 0;
}



