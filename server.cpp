#include <sys/socket.h>
#include <iostream>
#include <cctype>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/times.h>


int main() {

    int serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocketFD != -1)
        std::cout << "succes creating socket ID: " <<  serverSocketFD << std::endl;
    else
        std::cout << "failed creating socket!" << std::endl;

    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(4444);



    bind(serverSocketFD,(struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (bind(serverSocketFD,(struct sockaddr*)&serverAddress, sizeof(serverAddress)) == 0)
    {
        std::cout << "server is binded to port 4444 " << std::endl;
    }
    else 
        std::cout << "server failed to binded to port 4444 " << std::endl;


    if (listen(serverSocketFD, SOMAXCONN) == 0) {
        std::cout << "listening . . ." << std::endl;
    }

    else 
        std::cout << "failed to listening " << std::endl;

    struct timeval timeout;
    fd_set FDs, FDscopy;

    FD_ZERO(&FDs);
    FD_SET(serverSocketFD, &FDs);
    int fdmax = serverSocketFD;
    int fdnum;

    char buffer[1024];

    struct sockaddr_in connecClientAddress;
    memset(&connecClientAddress, 0, sizeof(connecClientAddress));

while (true) 
    {
        FDscopy = FDs;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        fdnum = select(fdmax+1, &FDscopy, 0, 0, &timeout);
        socklen_t clientaddrLenght = 0;
        int connectionServerSockFD = accept(serverSocketFD, (struct sockaddr*) &connecClientAddress, &clientaddrLenght);

        if (connectionServerSockFD == -1)
            std::cout << "failed to accept request"<< std::endl;

        else 
            std::cout << "request accepted at socket ID : "<< connectionServerSockFD <<std::endl;


        char receivedmsg[1024];
        memset(receivedmsg,0, sizeof(receivedmsg));

        recv(connectionServerSockFD, receivedmsg, 1024, 0);

        std::cout << receivedmsg << std::endl;

    }
    // close(connectionServerSockFD);
    // close(connectionServerSockFD);

    
}