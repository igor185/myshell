#include <unistd.h>
#include <string>
#include "internal/internal.hpp"
#include "util/util.hpp"

#include <iostream>
#include <cstring>

using namespace std;

int internal::mcd(std::vector<std::string> &args) {
    string path = args[0];

    size_t index = path.find('~');

    while (index != string::npos) {
        path = path.substr(0, index) + util::home_dir() + path.substr(index + 1);
        index = path.find('~');
    }

    int status = chdir(path.c_str());
    if(status){
        switch (errno) {
            case ENOENT:
                cerr << "No such directory: " << args[0] << endl;
                return ENOFILEORDIR;
            case ENOTDIR:
                cerr << "Not a directory: " << args[0] << endl;
                return ENOTADIR;
            case EACCES:
                cerr << "You don't have access to: " << args[0] << endl;
                return ENOACESS;
            default:
                cerr << strerror(errno) << endl;
                return ENKNOWN;
        }
    }

    return 0;
}