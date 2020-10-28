#include <iostream>

#include <IO/IO.h>


void IO::out(const std::string &line) {
    std::cout << line << std::flush;
}

void IO::outl(const std::string &line) {
    std::cout << line << std::endl;
}

void IO::err(const std::string &line) {
    std::cerr << line << std::endl;
}

void IO::err(int number) {
    std::cerr << number << std::endl;
}

void IO::help() {
    outl("Usage of myshell: \n"
         "[--server] - listen some port \n"
         "[--port number] - specify with port to listen \n"
         "[--help | -h]  print this message \n"
         "[filename] filename to execute from");
}