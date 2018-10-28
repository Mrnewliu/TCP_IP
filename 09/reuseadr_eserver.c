#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#define TRUE 1
#define FALSE 0

int main(int argc,char* argv[])
{
    int serv_sock,clnt_sock;
    char message[30];
    int option,str_len;
    socklen_t optlen,clnt_adr_sz;
    struct sockaddr_in serv_adr,clnt_adr;
    
    if(2 != argc)
    {
        printf("Usage: %s <port> \n",argv[0]);
        exit(-1);
    }

    serv_sock = socket(AF_INET, SOCK_STREAM, 0 );
    if(-1 == serv_sock)
    {
        perror("socket");
        exit(-1);
    }
    
    /*
        optlen = sizeof(option);
        option = TRUE;
        setsockopt(serv_sock,SOL_SOCKET,SO_RESUEADDR,(void*)&option,optlen):
    */

    bzero(&serv_adr,sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port = htons(atoi(argv[1]));
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr)) == -1)
    {
        perror("bind()");
        exit(-1);
    }
    if(listen(serv_sock, 5) == -1)
    {
        perror("listen");
        exit(-1);
    }
    clnt_adr_sz = sizeof(clnt_adr);
    clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_adr,&clnt_adr_sz);
    
    while((str_len = read(clnt_sock,message,sizeof(message))) != 0 )
    {
        write(clnt_sock,message, str_len);
        write(1,message,str_len);
    }

    close(clnt_sock);
    close(serv_sock);
    



    return 0;
}




