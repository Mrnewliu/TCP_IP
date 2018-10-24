#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

void error_handling(char* message);




int main(int argc,char* argv[])
{
    int sock_srv;
    int sock_clt;
    socklen_t clnt_addr_size;
    struct sockaddr_in server,client;
    char message[] = "helloworld";


    if(argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]); 
        exit(1);
    }
         

    sock_srv = socket(AF_INET, SOCK_STREAM, 0);
    if( sock_srv == -1)
    {
        error_handling("socket() erro");
    }
    
    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(atoi(argv[1]));

   
    if(bind(sock_srv,(struct sockaddr*)(&server),sizeof(server)) == -1)
    {
        error_handling("bind() error");
    }

    if(listen(sock_srv,5)== -1)
    {
        error_handling("listen() error");
    }
    
    clnt_addr_size = sizeof(client);
    sock_clt = accept(sock_srv,(struct sockaddr*)&client, &clnt_addr_size);
    if(sock_clt == -1)
    {
        perror("accept");
        error_handling("accept() error");

    }
    write(sock_clt,message,sizeof(message));    
    
    close(sock_srv);
    close(sock_clt);

    return 0;
}



void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}



