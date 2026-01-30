Assignment 3
Stimulus for question at position: 14
TCP Client Server Implmentation

In this assignment, write a C program for a TCP client that connects to the server. In this case

        The client connects to the server and requests a file to download from the server.
        The server accepts the connection and transfers the file to the client

Compile and run. Note: you may use the IP address 127.0.0.1 (loopback IP address) for a local host, i.e. both your client and server run on the same machine. Try to connect your client to a classmate’s server IP address (in the same network).

In general, a TCP server is designed as a concurrent server to serve multiple clients. This means when a client sends a request for a file transfer, the server accepts the connection request and spawns a thread to handle this transfer on the connection descriptor. The server will then continue in a loop, listening for another client connection request to handle another file transfer.

        1. Write a C program for a concurrent TCP server that accepts and responds to multiple client connection requests, each requesting a file transfer. In this case, the TCP server accepts a connection from a client, then spawns a separate thread to handle this specific client connection for file transfer.

You may use the following code template:

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

//Define the number of clients/threads that can be served
#define N 100
int threadCount = 0;
pthread_t clients[N]; //declaring N threads

 //Declare socket and connection file descriptors.

 //Declare receiving and sending buffers of size 10 bytes

 //Declare server address to which to bind for receiving messages and client address to fill in sending address

//Connection handler (thread function) for servicing client requests for file transfer
void* connectionHandler(void* sock){
   //declare buffer holding the name of the file from client

   //Connection established, server begins to read and write to the connecting client
   printf("Connection Established with client IP: %s and Port: %d\n", inet_ntoa(clienAddr.sin_addr), ntohs(clienAddr.sin_port));

	//receive name of the file from the client

   //open file and send to client

   //read file and send to connection descriptor

   printf("File transfer complete\n");

   //close file

   //Close connection descriptor

   pthread_exit(0);
}


int main(int argc, char *argv[]){
 //Get from the command line, server IP, src and dst files.
 if (argc != 2){
	printf ("Usage: %s <port #> \n",argv[0]);
	exit(0);
 }
 //Open a TCP socket, if successful, returns a descriptor


 //Setup the server address to bind using socket addressing structure


 //bind IP address and port for server endpoint socket


 // Server listening to the socket endpoint, and can queue 5 client requests
 printf("Server listening/waiting for client at port 5000\n");

 while (1){
   //Server accepts the connection and call the connection handler

   if(pthread_create(&clients[threadCount], NULL, connectionHandler, (void*) &connfd) < 0){
      perror("Unable to create a thread");
      exit(0);
   }
   else
      printf("Thread %d has been created to service client request\n",++threadCount);
 }
 for(int i = 0; i < threadCount; i++){
      pthread_join(clients[i], NULL);
 }
 return 0;
}
```
