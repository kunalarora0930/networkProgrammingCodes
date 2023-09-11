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

    // Connect to the server
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect");
        exit(1);
    }

    // Send data to the server
    char message[] = "Hello, world!";
    int send_len = send(sockfd, message, strlen(message), 0);
    if (send_len < 0)
    {
        perror("send");
        exit(1);
    }

    // Receive data from the server
    char buffer[1024];
    int recv_len = recv(sockfd, buffer, sizeof(buffer), 0);
    if (recv_len < 0)
    {
        perror("recv");
        exit(1);
    }

    printf("Received %d bytes from server: %s\n", recv_len, buffer);

    close(sockfd);

    return 0;
}