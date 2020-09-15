#include <iostream>

#include <internal/internal.hpp>
#include <util/util.hpp>

int internal::mpwd(std::vector<std::string> &args) {

    if (!args.empty()) {
        if (args.size() != 1 || !(args[0] == "-h" || args[0] == "--help")) {
            std::cout << errors::str_error(EARG) << std::endl;
            return EARG;
        }
        std::cout << "\nUsage: \n"
                  << "mpwd [-h|--help] print current directory \n"
                  << "[-h|--help] print this message\n"
                  << std::endl;

        return 0;
    }

    std::cout << util::pwd() << std::endl;

    return 0;
}