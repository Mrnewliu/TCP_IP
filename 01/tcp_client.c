#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<unistd.h>



void error_handling(char* message);

int main(int  argc,char* argv[])
{
    int i =0;
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len = 0;
    int index=0,read_len=0;

    if(argc != 3)
    {
        printf("Usage: %s <port>\n",argv[0]);
        exit(-1);
    }

    sock = socket(AF_INET,SOCK_STREAM, 0);
    if(sock == -1)
    {
        error_handling("socket() eror");
    }
    
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr)) == -1)
    { 
        perror("connect");
        error_handling("connect() error");
    }

    
    while( read_len = read(sock,&message[index++],1)) 
    {
    
        if(read_len == -1)
        {
            perror("read");
            error_handling("read() error");
        }

        str_len += read_len;
        for(i=0;i<3000;i++);
    }
    
    printf("Message from server:%s\n",message);
    printf("Function read call count:%d\n",str_len) ;

    close(sock);
    
    return 0;
}


void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

