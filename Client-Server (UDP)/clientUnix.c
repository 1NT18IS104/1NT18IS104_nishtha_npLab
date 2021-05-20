#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

int main(){
    struct sockaddr_in serverAddr;
    int clientsocket, portNum, nBytes;
    char buffer[1024];
    socklen_t addr_size;

    clientsocket=socket(PF_INET, SOCK_DGRAM,0);
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(7891);
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero,'\0',sizeof serverAddr.sin_zero);
    addr_size=sizeof(serverAddr);

    while(1){
	printf("Enter your message: \n");
	fgets(buffer,1024,stdin);
	printf("Your message: %s",buffer);
	nBytes=strlen(buffer)-1;
	sendto(clientsocket, buffer,nBytes,0,(struct sockaddr*)&serverAddr, addr_size);
        nBytes=recvfrom(clientsocket, buffer, 1024, 0, NULL, NULL);
        printf("Received from the server: %s\n",buffer);
    }
    return 0;
}
