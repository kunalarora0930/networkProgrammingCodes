#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define MAX_BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[MAX_BUFFER_SIZE];

    // Create a UDP socket
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    printf("Connected to the Chat Server at %s:%d\n", SERVER_IP, PORT);

    while (1) {
        // Send data to the server
        printf("Client (You): ");
        fgets(buffer, sizeof(buffer), stdin);
        if (sendto(client_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
            perror("Send error");
            break;
        }

        if (strcmp(buffer, "exit\n") == 0) {
            printf("Chat ended.\n");
            break;
        }

        // Receive data from the server
        ssize_t received_bytes = recvfrom(client_socket, buffer, sizeof(buffer), 0, NULL, NULL);
        if (received_bytes == -1) {
            perror("Receive error");
            break;
        }

        buffer[received_bytes] = '\0';
        printf("Server: %s\n", buffer);

        if (strcmp(buffer, "exit\n") == 0) {
            printf("Chat ended.\n");
            break;
        }
    }

    // Close the client socket
    close(client_socket);

    return 0;
}
