#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 6969
#define BUFFER_SIZE 1024


int main() {
    // create a network socket
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];

    // create server socket
    if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;


    // bind socket to address and port
    if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        printf("Error");
        exit(EXIT_FAILURE);
    }

    // listen to incoming connection
    if(listen(server_socket, 5) == -1) {
        // error
        exit(EXIT_FAILURE);
    }

    printf("Listening on port %d", PORT);
    socklen_t addr_size = sizeof(client_addr);

    while (1)
    {
        // accept connection
        if((client_socket = accept(server_socket, (struct sockaddr*)& client_addr, &addr_size)) == -1) {
            printf("Connection not accepted\n");
            exit(EXIT_FAILURE);
        }

        printf("Accepted\n");
        size_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

        if (bytes_received == -1) {
            perror("Error while receiving data");
            close(client_socket);
            continue;
        }

        // echo back data to client
        size_t bytes_sent = send(client_socket, buffer, bytes_received, 0);

        if(bytes_sent == -1) {
            printf("Error");
        }
        
        close(client_socket);

        
    }

    close(server_socket);


    return 0;    

}