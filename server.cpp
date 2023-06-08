
#include <sys/socket.h>
#include <iostream>
#include <cctype>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/times.h>

int main() {
    // Create a socket
    int serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocketFD != -1)
        std::cout << "Successfully created socket ID: " << serverSocketFD << std::endl;
    else {
        std::cout << "Failed to create socket!" << std::endl;
        return(1);
    }

    // Set up server address
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(4444);

    // Bind the socket to a specific address and port
    bind(serverSocketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (bind(serverSocketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == 0) {
        std::cout << "Server is binded to port 4444" << std::endl;
    }
    else {
        std::cout << "Server failed to bind to " << std::endl;
    }

        // Listen for incoming connections
        if (listen(serverSocketFD, SOMAXCONN) == 0) {
            std::cout << "Listening..." << std::endl;
        }
        else {
            std::cout << "Failed to listen" << std::endl;
        }

        
    while (true) {

        struct timeval timeout;
        fd_set FDs, FDscopy;

        FD_ZERO(&FDs);
        FD_SET(serverSocketFD, &FDs);
        int fdmax = serverSocketFD;
        int fdnum;

        struct sockaddr_in connecClientAddress;
        memset(&connecClientAddress, 0, sizeof(connecClientAddress));
        FDscopy = FDs;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        // Wait for activity on the socket using select
        fdnum = select(fdmax + 1, &FDscopy, 0, 0, &timeout);

        // Accept the incoming connection request
        socklen_t clientaddrLenght = 0;
        int connectionServerSockFD = accept(serverSocketFD, (struct sockaddr*)&connecClientAddress, &clientaddrLenght);

        if (connectionServerSockFD == -1) {
            std::cout << "Failed to accept request" << std::endl;
            return 1;
        }
        else {
            std::cout << "Request accepted at socket ID: " << connectionServerSockFD << std::endl;
            continue;
        }

        char receivedmsg[1024];
        memset(receivedmsg, 0, sizeof(receivedmsg));

        // Receive data from the client
        recv(connectionServerSockFD, receivedmsg, 1024, 0);

        std::cout << receivedmsg << std::endl;
    }

    return 0;
}
