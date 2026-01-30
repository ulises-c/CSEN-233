rm -f server.out client.out downloaded_file.txt
gcc server.c -o server.out -pthread
gcc client.c -o client.out
./server.out 5001 &
sleep 1
# Usage: ./client <IP> <PORT> <FILENAME>
./client.out 127.0.0.1 5001 test.txt
