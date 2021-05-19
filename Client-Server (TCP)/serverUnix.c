#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>

int main(){
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int sock, connected, bytes_recv;
    char send_data[1024], recv_data[1024];
    socklen_t sin_size;
    if((sock=socket(AF_INET, SOCK_STREAM, 0))==-1) {
        perror("socket");
        exit(1);
    }
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(6000);
    server_addr.sin_addr.s_addr=INADDR_ANY;
    if(bind(sock,(struct sockaddr*)&server_addr, sizeof(struct sockaddr))==-1){
        perror("Unable to bind");
        exit(1);
    }

    if(listen(sock, 5)==-1){
        perror("listen");
        exit(1);
    }

    printf("TCP server is waiting for client on port xxxx\n");
    sin_size= sizeof(struct sockaddr_in);
    connected= accept(sock,(struct sockaddr*)& client_addr, &sin_size);
    while(1){
        printf("Enter the message to be sent \n(press q to exit)\n");
        fgets(send_data, 0124, stdin);
        if(strcmp(send_data, "q")==0){
            send(connected, send_data, strlen(send_data),0);
            close(connected);
            break;
        }
        else{
            send(connected, send_data, strlen(send_data),0);
            bytes_recv=recv(connected, recv_data, 1024, 0);
            recv_data[bytes_recv]='\0';
        }
        if(strcmp(recv_data, "q")==0){
            close(connected);
            break;
        }
        else{
            printf("Received data is: \n%s\n",recv_data);
        }
        close(sock);
        return 0;
    }
}
