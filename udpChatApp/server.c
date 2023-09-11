#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 12345
#define MAX_BUFFER_SIZE 1024

int main() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[MAX_BUFFER_SIZE];

    // Create a UDP socket
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Chat Server is running on port %d...\n", PORT);

    while (1) {
        // Receive data from the client
        ssize_t received_bytes = recvfrom(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &client_addr_len);
        if (received_bytes == -1) {
            perror("Receive error");
            break;
        }

        buffer[received_bytes] = '\0';
        printf("Client: %s\n", buffer);

        if (strcmp(buffer, "exit\n") == 0) {
            printf("Chat ended.\n");
            break;
        }

        // Send data to the client
        printf("Server (You): ");
        fgets(buffer, sizeof(buffer), stdin);
        if (sendto(server_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, client_addr_len) == -1) {
            perror("Send error");
            break;
        }

        if (strcmp(buffer, "exit\n") == 0) {
            printf("Chat ended.\n");
            break;
        }
    }

    // Close the server socket
    close(server_socket);

    return 0;
}
