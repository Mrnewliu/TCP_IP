#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>


#define BUF_SIZE 1024


int main(int argc,char* argv[])
{
    char message[BUF_SIZE];
    int str_len = 0;
    int serv_sock,clnt_sock;
    int i = 0;
    
    struct sockaddr_in serv_adr,clnt_adr;
    socklen_t clnt_adr_sz;

    if(2 != argc)
    {
        printf("Usage: %s <port>\n",argv[0]);
        exit(-1);
    }
    
    
    

    serv_sock = socket(AF_INET,SOCK_STREAM,0);
    if(-1 == serv_sock)
    {
        perror("socket");
        exit(-1);
    }
    bzero(&serv_adr,sizeof(serv_adr));    
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port = htons(atoi(argv[1]));
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(serv_sock,(struct sockaddr*)(&serv_adr),sizeof(serv_adr))== -1)
    {
        perror("bind");
        exit(-1);
    }




    if(listen(serv_sock,5) == -1)
    {
        perror("listen");
        exit(-1);
    }

    clnt_adr_sz = sizeof(clnt_adr);

    for(i=0;i<5;i++)
    {
        clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_adr,&clnt_adr_sz);
        if( clnt_sock == -1)
        {
            perror("accept");
            exit(-1);
        }
        else
        {
            printf("connect client %d\n", i+1);    
        
        }
        
        while( (str_len = read(clnt_sock,message,BUF_SIZE)) != 0 )
        {
            if( str_len == -1)
            {   
                perror("read");
                break;
            }
            else
            {
                write(clnt_sock,message,str_len);
            }
        }
        close(clnt_sock);
    }
    

   close(serv_sock);
    

    return 0;
}




