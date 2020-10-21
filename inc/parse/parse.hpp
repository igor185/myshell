#pragma once

#include <string>
#include <vector>

namespace parse {
    struct Arg {
        std::vector<std::string> args;
        int ifd;
        int ofd;
        int efd;
    };

    struct Args{
        std::vector<Arg> args;
        bool in_current_process;
    };
    Args parse_line(std::string& s);
}