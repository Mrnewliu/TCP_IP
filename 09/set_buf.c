#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<sys/socket.h>

int main(int argc,char* argv[])
{
    int sock;
    int snd_buf = 1024*3,rcv_buf=1024*3;
    int state;
    socklen_t len;


    sock = socket(AF_INET, SOCK_STREAM, 0);
    if( -1 == sock)
    {
        perror("socket");
        exit(-1);
    }
    
    state = setsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void*)&rcv_buf,sizeof(rcv_buf));
    if(state)
    {
        perror("setsockopt");
        exit(-1);
    }

    
    state = setsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&rcv_buf,sizeof(snd_buf));
    if(state)
    {
        perror("setsockopt");
        exit(-1);
    }


    len = sizeof(snd_buf);

    state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf,&len);
    if(state)
    {
        perror("getsockopt");
        exit(-1);
    }
      
    len = sizeof(rcv_buf); 
    state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF,(void*)&rcv_buf,&len);
    if(state)
    {
        perror("getsockopt");
        exit(-1);
    }
    
    printf("Input buf size: %d \n",rcv_buf);
    printf("Output buf size: %d \n",snd_buf);

        

    return 0;
}



