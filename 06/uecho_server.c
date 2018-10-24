#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>


#define BUF_SIZE  30    

int main(int argc,char* argv[])
{
    int sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t clnt_adr_sz;
    struct sockaddr_in serv_adr,clnt_adr;
    if( 2 != argc )
    {
        printf("Usage:%s <port>\n",argv[0]);
        exit(-1);
    }
    
    sock = socket(AF_INET,SOCK_DGRAM,0); 
    if( -1 == sock )
    {
        perror("socket"); 
        exit(-1);
    }
    
    bzero(&serv_adr,sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));   
    
    if( bind(sock,(struct addrsock*)&serv_adr,sizeof(serv_adr)) == -1)
    {
        perror("bind");    
        exit(-1);
    }
    
    while(1)
    {
        clnt_adr_sz = sizeof(clnt_adr);
        str_len = recvfrom(sock,message,BUF_SIZE,0,(struct sockaddr*)&clnt_adr,&clnt_adr_sz);
        sendto(sock,message,str_len,0,(struct sockaddr*)&clnt_adr,clnt_adr_sz);
    }

        
    close(sock);


    

    return 0;
}




