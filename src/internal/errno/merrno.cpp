#include <iostream>

#include <internal/internal.hpp>
#include <util/util.hpp>

int internal::merrno(std::vector<std::string> &args) {
    bool is_string = false;
    bool is_print_help = false;
    for (auto &i: args) {
        if (i == "-h" || i == "--help")
            is_print_help = true;
        else if (i == "-s")
            is_string = true;
        else {
            errors::set_error(EARG);
            std::cout << errors::str_error(EARG) << std::endl;
            return EARG;
        }
    }
    if (is_print_help) {
        std::cout << "\nUsage: \n"
                  << "merrno [-h|--help] [-s] print status of previously executed program \n"
                  << "[-h|--help] print this message"
                  << "[-s] print string representation of error"
                  << std::endl;

        return 0;
    }

    int error = errors::get_error();
    if (is_string)
        std::cout << errors::str_error(error) << std::endl;
    else
        std::cout << error << std::endl;

    return 0;
}
