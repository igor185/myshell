#include <internal/internal.hpp>
#include <util/util.h>
#include <IO/IO.h>

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
            IO::err(errors::str_error(EARG));
            return EARG;
        }
    }
    if (is_print_help) {
        IO::outl("\nUsage: \n merrno "
                 "[-h|--help] [-s] print status of previously executed program \n"
                 "[-h|--help] print this message"
                 "[-s] print string representation of error");

        return 0;
    }

    int error = errors::get_error();
    if (is_string) {
        IO::err(errors::str_error(error));
    } else {
        IO::err(error);
    }


    return 0;
}
