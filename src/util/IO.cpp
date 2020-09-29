#include <iostream>

#include <IO/IO.h>


void IO::out(const std::string &line) {
    std::cout << line;
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