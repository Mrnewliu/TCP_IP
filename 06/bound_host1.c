#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#define BUF_SIZE  30

int main(int argc,char* argv[])
{
    int sock;
    char message[BUF_SIZE];
    struct sockaddr_in my_adr,your_adr;
    
    socklen_t adr_sz;
    int str_len,i;
    
    if(2 != argc)
    {
        printf("Usage:%s <port>\n",argv[0]);
        exit(-1);
    }

    sock = socket(AF_INET,SOCK_DGRAM,0);
    if( -1 == sock)
    {
        perror("socket");
        exit(-1);
    }

    bzero(&my_adr,sizeof(my_adr));
    my_adr.sin_family = AF_INET;
    my_adr.sin_port = htons(atoi(argv[1]));
    my_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    if( bind(sock,(struct sockaddr*)&my_adr,sizeof(my_adr)) == -1)
    {
        perror("bind");
        exit(-1);
    }
    
    for(i=0;i<3;i++)
    {
//        sleep(5); 
        adr_sz = sizeof(your_adr);
        str_len = recvfrom(sock,message,BUF_SIZE,0,(struct sockaddr*)&your_adr,&adr_sz);
        printf("Message: %d: %s \n",i+1,message);

    }
    
    
    close(sock);

    


    return 0;
}


