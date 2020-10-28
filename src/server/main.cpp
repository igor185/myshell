#include <unistd.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <semaphore.h>
#include <fcntl.h>
#include <arpa/inet.h>


#include <util/util.h>
#include <IO/IO.h>

#define MAX_CONNECT 100
#define BUF_SIZE 1024
char buffer[BUF_SIZE + 1];


std::string receive(int fd){
    int cc = 0;
    std::string res;
    do {
        cc = recv(fd, buffer, sizeof(buffer), 0);
        buffer[cc] = '\0';
        res += buffer;
    }while (cc == BUF_SIZE);

    return res;
}

void server::init(int port) {
    struct sockaddr_in addr;

    parse::Args args;

    int sfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sfd == -1) {
        IO::err(std::strerror(errno));
        exit(EXIT_FAILURE);
    }


    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    int res = bind(sfd, (struct sockaddr *) &addr, sizeof(addr));

    if (res == -1) {
        IO::err(std::strerror(errno));
        IO::err(std::to_string(port));
        exit(EXIT_FAILURE);
    }

    listen(sfd, MAX_CONNECT);

    IO::outl("Listen port: " + std::to_string(port));

    sem_t sem;
    sem_init(&sem, O_WRONLY, 1);
    int std_out = dup(STDOUT_FILENO);

    while (true) {
        int client_sfd = accept(sfd, 0, 0);

        if (client_sfd == -1) {
            IO::err(std::strerror(errno));
            exit(EXIT_FAILURE);
        }

        pid_t pid = fork();

        std::string msg;

        if (pid == -1) {
            IO::err(std::strerror(errno));
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            close(client_sfd);
            continue;
        }

        struct sockaddr_in addr_client{};
        socklen_t addr_size = sizeof(struct sockaddr_in);

        getpeername(client_sfd, (struct sockaddr *)&addr_client, &addr_size);

        msg = "Client fd: " + std::to_string(client_sfd) + ", ip: " + inet_ntoa(addr_client.sin_addr) + "\n";

        sem_wait(&sem);
        util::print_log(std_out, msg.c_str(), msg.size());
        sem_post(&sem);

        dup2(client_sfd, STDOUT_FILENO);
        dup2(client_sfd, STDERR_FILENO);


        while (true) {
            IO::out(util::get_promt());
            std::cout.flush();


            std::string line = receive(client_sfd);

            msg = "Client with descriptor " + std::to_string(client_sfd) + ": " + line + "\n";

            std::cout << "sem wait" << std::endl;
            sem_wait(&sem);
            util::print_log(std_out, msg.c_str(), msg.size());
            sem_post(&sem);
            std::cout << "sem post" << std::endl;

            if (line.empty()){
                sem_close(&sem);
                exit(EXIT_SUCCESS);
            }
            args = parse::parse_line(line);

            if (!args.args.empty() && !args.args[0].args.empty()) {
                if(args.in_current_process) {
                    util::run_program(args);
                } else
                    util::run_program_in_process(args);
            }
            std::cout.flush();
        }
    }
}