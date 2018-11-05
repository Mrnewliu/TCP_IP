#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<sys/select.h>


#define BUF_SIZE 30

int main(int argc,char* argv[])
{
    int serv_sock,clnt_sock;
    struct sockaddr_in  serv_adr,clnt_adr;
    struct timeval timeout;
    fd_set reads,cpy_reads;
    
    socklen_t adr_sz;

    int fd_max, str_len,fd_num,i;
    char buf[BUF_SIZE];
    
    if( argc != 2)
    {
        printf("Usage: %s <prt>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket( AF_INET, SOCK_STREAM, 0 );
    memset(&adr_sz, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if( bind(serv_sock,(struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
    {
        perror("bind()\n");
        exit(-1);
    }

    if(listen(serv_sock, 5) == -1)    
    {
        perror("listen");
        exit(-1);
    }

    






    



    
    return 0;
}




