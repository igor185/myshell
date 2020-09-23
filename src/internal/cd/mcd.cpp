#include <unistd.h>
#include <string>
#include <cstring>

#include <internal/internal.hpp>
#include <util/util.h>
#include <IO/IO.h>


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
                IO::err("No such directory: " + args[0]);
                return ENOFILEORDIR;
            case ENOTDIR:
                IO::err("Not a directory: " + args[0]);
                return ENOTADIR;
            case EACCES:
                IO::err("You don't have access to: " + args[0]);
                return ENOACESS;
            default:
                IO::err(strerror(errno));
                return ENKNOWN;
        }
    }

    return 0;
}