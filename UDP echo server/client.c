#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

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
    server_addr.sin_addr.s_addr = INADDR_ANY;

    printf("Enter a message to send to the server: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strlen(buffer) - 1] = '\0';  // Remove the newline character

    // Send the user's message to the server
    if (sendto(client_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Send error");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("Message sent to server: %s\n", buffer);

    // Receive the echoed message from the server
    ssize_t received_bytes = recvfrom(client_socket, buffer, sizeof(buffer), 0, NULL, NULL);
    if (received_bytes == -1) {
        perror("Receive error");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    buffer[received_bytes] = '\0';
    printf("Received message from server: %s\n", buffer);

    // Close the client socket
    close(client_socket);

    return 0;
}
