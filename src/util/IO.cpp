#include <iostream>

#include <IO/IO.h>

using namespace std;

void IO::out(const std::string &line) {
    cout << line;
}

void IO::outl(const std::string &line) {
    cout << line << endl;
}

void IO::err(const std::string &line) {
    cerr << line << endl;
}

void IO::err(int number) {
    cerr << number << endl;
}