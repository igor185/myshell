#ifndef IO
#define IO

#include <string>

namespace IO {
    void out(const std::string& line);

    void outl(const std::string& line);

    void err(const std::string& line);

    void err(int number);
}

#endif