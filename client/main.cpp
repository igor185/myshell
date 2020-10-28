#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
char buffer[BUF_SIZE + 1];


void read_socket(int fd){
//    std::cout << "read socket in" << std::endl;
    int bread = 0;
    do {
        bread = recv(fd, buffer, BUF_SIZE, 0);
        if(bread == -1){
            std::cout << std::strerror(errno) << std::endl;
            exit(EXIT_SUCCESS);
        }

        if(bread > 0) {
            std::cout << buffer << std::flush;
        }
    }while (bread == BUF_SIZE);
    std::cout << "read socket out" << std::flush;
}


int main() {
    struct sockaddr_in server = {};

    int sd = socket (AF_INET,SOCK_STREAM,0);
    if( sd == -1 ) {
        std::cout << std::strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    memset(&server, 0, sizeof( server ));
    server.sin_family = AF_INET;
    server.sin_port = htons(2233);

    int res = connect(sd, (struct sockaddr *) &server, sizeof(server));
    if(res == -1){
        std::cout << "Connect error: " << std::strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string msg;

    read_socket(sd);

//    std::cout << "loop" << std::endl;
    while(std::getline(std::cin, msg)){
//        std::cout << "sending" << std::endl;
        send(sd, msg.c_str(), msg.size(), 0);
//        std::cout << "after send" << std::endl;
//        std::cout << "send" << std::endl;
//        sleep(2);
        read_socket(sd);
        read_socket(sd);
    }

    return EXIT_SUCCESS;
}
