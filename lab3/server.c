#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SIZE 1024
#define N 100 // Max clients

// Structure to pass client info safely to the thread
typedef struct
{
    int sockfd;
    struct sockaddr_in clientAddr;
} client_info;

// Thread function to handle file transfer
void *connectionHandler(void *arg)
{
    // 1. Unpack the arguments
    client_info *cinfo = (client_info *)arg;
    int connfd = cinfo->sockfd;
    struct sockaddr_in clientAddr = cinfo->clientAddr;

    // Detach thread so resources are reclaimed automatically upon exit
    pthread_detach(pthread_self());

    char filename[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    FILE *fp;

    printf("Connection Established with client IP: %s and Port: %d\n",
           inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

    // 2. Receive filename from client
    memset(filename, 0, sizeof(filename));
    int n = recv(connfd, filename, sizeof(filename) - 1, 0);

    if (n <= 0)
    {
        printf("Client disconnected or error reading filename.\n");
        close(connfd);
        free(cinfo);
        pthread_exit(NULL);
    }

    // Ensure string is null-terminated (remove newline if present)
    filename[n] = '\0';
    filename[strcspn(filename, "\n")] = 0;

    printf("Client requested file: %s\n", filename);

    // 3. Open file and send to client
    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        printf("File '%s' not found. Sending error.\n", filename);
        char *msg = "ERROR: File not found";
        send(connfd, msg, strlen(msg), 0);
    }
    else
    {
        // Read file in chunks and send
        int bytesRead;
        while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, fp)) > 0)
        {
            send(connfd, buffer, bytesRead, 0);
        }
        printf("File transfer complete for %s\n", inet_ntoa(clientAddr.sin_addr));
        fclose(fp);
    }

    // 4. Cleanup
    close(connfd);
    free(cinfo); // Free the memory allocated in the main loop
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <port #>\n", argv[0]);
        exit(0);
    }

    int listenfd, connfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size;
    pthread_t tid;

    // 1. Open TCP socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
    {
        perror("Socket creation failed");
        exit(1);
    }

    // 2. Setup Server Address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[1]));
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

    // 3. Bind
    if (bind(listenfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("Bind failed");
        exit(1);
    }

    // 4. Listen
    if (listen(listenfd, 5) < 0)
    {
        perror("Listen failed");
        exit(1);
    }

    printf("Server listening/waiting for clients at port %s\n", argv[1]);

    // 5. Main Loop to accept clients
    while (1)
    {
        addr_size = sizeof(clientAddr);
        connfd = accept(listenfd, (struct sockaddr *)&clientAddr, &addr_size);

        if (connfd < 0)
        {
            perror("Accept failed");
            continue;
        }

        // Allocate memory for client info to prevent race conditions
        client_info *cinfo = malloc(sizeof(client_info));
        cinfo->sockfd = connfd;
        cinfo->clientAddr = clientAddr;

        // Spawn thread
        if (pthread_create(&tid, NULL, connectionHandler, (void *)cinfo) != 0)
        {
            perror("Unable to create thread");
            close(connfd);
            free(cinfo);
        }
        // Note: We do not join threads here because we want to keep accepting new clients immediately.
        // Threads detach themselves inside the handler function.
    }

    close(listenfd);
    return 0;
}