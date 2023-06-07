#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>

int socket(int doamin, int type, int protocol);

int main() {
    int clientsockFD = socket(AF_INET,SOCK_STREAM, 0);
    if (clientsockFD != -1)
        std::cout << "sockID " << clientsockFD << std::endl;
    else 
        std::cout << "error " << std::endl;

    struct sockaddr_in serverAdrees;
    memset (&serverAdrees, 0, sizeof(serverAdrees));

    serverAdrees.sin_family = AF_INET;
    serverAdrees.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAdrees.sin_port = htons(4444);

    if (connect(clientsockFD, (struct sockaddr *) &serverAdrees, sizeof(serverAdrees)) == 0)
    {
        std::cout << "connect succeful !" << std::endl;
    }
    else 
    {
        std::cout << "Error: did not connect "<< std::endl;
    }

    char buff[1024] = "hello i'am youssef";

    send(clientsockFD, buff, strlen(buff), 0);
    memset(buff, 0 , 1024);
    recv(clientsockFD, buff, 1024, 0);



} 