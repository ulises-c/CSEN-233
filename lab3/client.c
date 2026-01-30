#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <server_ip> <port> <filename_to_request>\n", argv[0]);
        exit(0);
    }

    char *server_ip = argv[1];
    int port = atoi(argv[2]);
    char *filename = argv[3];

    int sockfd;
    struct sockaddr_in servAddr;
    char buffer[BUFFER_SIZE];

    // 1. Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Setup server address
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, server_ip, &servAddr.sin_addr) <= 0)
    {
        perror("Invalid address/Address not supported");
        exit(EXIT_FAILURE);
    }

    // 3. Connect to server
    if (connect(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server at %s:%d\n", server_ip, port);

    // 4. Send filename to server
    send(sockfd, filename, strlen(filename), 0);
    printf("Requesting file: %s\n", filename);

    // 5. Receive file data
    // We save to a different name to avoid overwriting your source file if testing in the same folder
    FILE *file = fopen("downloaded_file", "wb");
    if (file == NULL)
    {
        perror("Failed to create file on disk");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    int bytesReceived;
    int isError = 0;

    // Read loop
    while ((bytesReceived = recv(sockfd, buffer, BUFFER_SIZE, 0)) > 0)
    {
        // Check for server error message (simple check)
        if (strncmp(buffer, "ERROR", 5) == 0)
        {
            printf("Server response: %s\n", buffer);
            isError = 1;
            break;
        }
        fwrite(buffer, 1, bytesReceived, file);
    }

    fclose(file);
    close(sockfd);

    if (isError)
    {
        remove("downloaded_file"); // Delete the empty/error file
        printf("Download failed.\n");
    }
    else
    {
        printf("File download completed. Saved as 'downloaded_file'\n");
    }

    return 0;
}