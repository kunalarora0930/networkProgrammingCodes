#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT 8080

int main()
{
    // Create a UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(1);
    }

    // Bind the socket to the server port
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind");
        exit(1);
    }

    // Receive data from the client
    char buffer[1024];
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int recv_len = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &client_addr_len);
    if (recv_len < 0)
    {
        perror("recvfrom");
        exit(1);
    }

    // Echo the data back to the client
    int send_len = sendto(sockfd, buffer, recv_len, 0, (struct sockaddr *)&client_addr, client_addr_len);
    if (send_len < 0)
    {
        perror("sendto");
        exit(1);
    }

    printf("Received %d bytes from client: %s\n", recv_len, buffer);

    close(sockfd);

    return 0;
}