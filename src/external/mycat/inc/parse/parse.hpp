#ifndef MYCAT_PARSE_HPP
#define MYCAT_PARSE_HPP

#include <vector>
#include <string>

namespace parse {
    struct Args {
        std::vector<std::string> file_names;
        bool A;
    };

    parse::Args parse_ags(int argc, char **argv);
}

#endif

