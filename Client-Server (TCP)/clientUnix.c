#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>
#include<unistd.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>

int main(){
    struct sockaddr_in server_addr;
    int sock, bytes_recv;
    char send_data[1024], recv_data[1024];
    if((sock=socket(AF_INET, SOCK_STREAM, 0))==-1) {
        perror("socket");
        exit(1);
    }
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(6000);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(connect(sock,(struct sockaddr*)&server_addr, sizeof(struct sockaddr))==-1){
        perror("connect");
        exit(1);
    }

    while(1){
        bytes_recv=recv(sock, recv_data, 1024, 0);
        recv_data[bytes_recv]=0;
        if(strcmp(recv_data, "q")==0){
            close(sock);
            break;
        }
        else{
            printf("Received data is: \n%s\n",recv_data);
        }
        printf("send q to quit\n");
        fgets(send_data, 1024, stdin);
        if(strcmp(send_data, "q")==0){
            send(sock, send_data, strlen(send_data),0);
            close(sock);
            break;
        }
        else{
            send(sock, send_data, strlen(send_data),0);
        }
        
        return 0;
    }
}
