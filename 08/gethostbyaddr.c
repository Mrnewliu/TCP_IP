#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>


int main(int argc,char* argv[])
{
    int i;
    struct hostent *host;
    struct sockaddr_in addr;
    if(2 != argc)
    {
        printf("Usage: %s <IP>\n",argv[0]);
        exit(-1);
    }

    //bzero(&addr,sizeof(addr));
    memset(&addr,0,sizeof(addr));
   // addr.sin_family = AF_INET;
   // addr.sin_port = htons();
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    host = gethostbyaddr((char*)&addr.sin_addr,4,AF_INET);
    
    if(!host)
    {
        perror("gethostbyaddr");
        //exit(-1);
    }
    
    
   printf("Office name:%s \n",host->h_name);
    
    for(i=0;i<host->h_aliases[i];i++)
    {
        printf("Aliases %d: %s \n",i+1,host->h_aliases[i]);
    }
    printf("Address type: %s\n",(host->h_addrtype == AF_INET)?"AF_INET":"AF_INET6");
    for(i=0;i<host->h_aliases[i];i++)
    {
        printf("IP addr %d: %s \n",i+1,inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));

    }
    
    

    return 0;
}



