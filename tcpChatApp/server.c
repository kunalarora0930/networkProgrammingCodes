#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 6969
#define BUFFER_SIZE 1024

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    char buffer[BUFFER_SIZE];


    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    listen(server_socket, 5);

    client_socket = accept(server_socket, (struct sockaddr*) &client_addr, &client_addr_len);

    while(1) {
        size_t recieved_bytes = recv(client_socket, buffer, sizeof(buffer));

        buffer[recieved_bytes] = '\0';
        printf("Client: %s\n", buffer);


        printf("Enter your message: ");

        fgets(buffer, sizeof)
    }

}


