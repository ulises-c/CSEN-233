rm -f server client downloaded_file
gcc server.c -o server -pthread
gcc client.c -o client
./server 5001 &
sleep 1
# Usage: ./client <IP> <PORT> <FILENAME>
./client 127.0.0.1 5001 test.txt
