#ifndef PARSE
#define PARSE

#include <string>
#include <vector>

namespace parse {
    struct Args {
        bool is_valid;
        std::string s;
        std::vector<std::string> args;
    };

    Args parse_line(std::string& s);
}

#endif