#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include <ctype.h>

int main(){
    struct sockaddr_in serverAddr, clientAddr;
    struct sockaddr_storage serverStorage;
    int udpsocket, nBytes, i;
    char buffer[1024];
    socklen_t addr_size, client_addr_size;

    udpsocket=socket(PF_INET, SOCK_DGRAM,0);
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(7891);
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero,'\0',sizeof serverAddr.sin_zero);
    bind(udpsocket,(struct sockaddr*)&serverAddr, sizeof(serverAddr));
    addr_size=sizeof(serverStorage);

    while(1){
	    printf("Listening for incoming messages...\n\n");
            nBytes=recvfrom(udpsocket, buffer, 1024,0, (struct sockaddr*) &serverStorage, &addr_size);
	    printf("Message from client: \n");
            for(i=0;i<nBytes;i++)
		printf("%c",buffer[i]);
	    printf("\n");
            for(i=0;i<nBytes;i++)
		buffer[i]=toupper(buffer[i]);
	    sendto(udpsocket, buffer, nBytes,0, (struct sockaddr*) &serverStorage, addr_size);
        }
        return 0;
}
