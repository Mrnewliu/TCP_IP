#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#define BUF_SIZE 30

int main(int argc,char* argv[])
{
    int serv_sd,clnt_sd;
    FILE* fp;

    char buf[BUF_SIZE];
    int read_cnt;

    struct sockaddr_in serv_adr,clnt_adr;
    socklen_t clnt_adr_sz;
    
    if( 2 != argc)
    {
        printf("Usage: %s <port>\n",argv[0]);
        exit(-1);
    }

    serv_sd = socket(AF_INET,SOCK_STREAM, 0);
    if(-1 == serv_sd )
    {
        perror("socket");
        exit(-1);
    }
    fp = fopen("file_server.c","rb");
    
    bzero(&serv_adr,sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port  = htons(atoi(argv[1]));
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);

    if( bind(serv_sd,(struct sockaddr*)&serv_adr,sizeof(serv_adr)) == -1)
    {
        perror("bind");
        exit(-1);
    }
    
    listen(serv_sd, 5);

    clnt_adr_sz = sizeof(clnt_adr);
    clnt_sd = accept( serv_sd, (struct sockaddr*)&clnt_adr,&clnt_adr_sz);

    while(1)
    {
        read_cnt = fread((void*)buf,1,BUF_SIZE,fp);
        if( read_cnt < BUF_SIZE)
        {
            write(clnt_sd,buf,BUF_SIZE);
            break;
        }
        write(clnt_sd,buf,BUF_SIZE);
    }
    
    shutdown( clnt_sd, SHUT_WR);
    read(clnt_sd,buf,BUF_SIZE);
    printf("Message from client: %s\n", buf);

    fclose(fp);
    close(serv_sd);
    close(clnt_sd);
    
    
    
    
    
    
    
    return 0;
}



