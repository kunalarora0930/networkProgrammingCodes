#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 6969
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main() {


    int client_socket;
    struct sockaddr_in server_addr;

    char buffer[BUFFER_SIZE];

    // create a socket
    if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Error creating socket" );
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    
    // connect to server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected\n");

    while(1) {
        printf("Enter your message: ");
        fgets(buffer, sizeof(buffer), stdin);


        //send data
        ssize_t bytes_sent = send(client_socket, buffer, strlen(buffer),0);
        if(bytes_sent == -1) {
            printf("Error");
        }

        if(strcmp(buffer, "exit\n") == 0) {
            printf("Exiting ....\n");
            break;
        }

        int bytes_recieved = recv(client_socket, buffer, sizeof(buffer), 0);
        printf("message recieved from server: %s", buffer);
        // close(client_socket);
    }
    close(client_socket);
    return 0;

}