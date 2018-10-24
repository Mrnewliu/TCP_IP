#include<stdio.h>
#include<stdlib.h>

#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fcntl.h>




#define BUF_SIZE 1024
#define OPSZ     4
#define RLSZ     4


int main(int argc,char* argv[])
{
    int sock;
    struct sockaddr_in serv_adr;
    char opmsg[BUF_SIZE];
    int result,opnd_cnt,i;

    if( 3 != argc )
    {
        printf("Usage:%s <ip> <port>\n",argv[0]);
        exit(-1);
    }

    sock = socket(AF_INET,SOCK_STREAM,0);
    if( -1  == sock)
    {
        perror("socket");
        exit(-1);
    }
    
    bzero(&serv_adr,sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port = htons(atoi(argv[2]));
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);



    if(connect(sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr)) == -1)
    {
        perror("connect");
        exit(-1);
    }

    else
    {
        printf("Connect....\n");

    }
    fputs("Operand count: ",stdout);
    scanf("%d",&opnd_cnt);
    opmsg[0] = (char)opnd_cnt;

    for(i=0;i<opnd_cnt;i++)
    {
        printf("Operand %d: ",i+1);
        scanf("%d",(int*)&opmsg[OPSZ*i+1]);

    }

    fgetc(stdin);
    fputs("Operator: ",stdout);
    scanf("%c", &opmsg[opnd_cnt*OPSZ+1]);
    write(sock,opmsg,opnd_cnt*OPSZ+2);
    read(sock,&result,RLSZ);

    printf("Operation result: %d \n",result);
    
    close(sock);
    
    return 0;
}






