#include <internal/internal.hpp>
#include <util/util.h>
#include <IO/IO.h>

int internal::mpwd(std::vector<std::string> &args) {

    if (!args.empty()) {
        if (args.size() != 1 || !(args[0] == "-h" || args[0] == "--help")) {
            IO::err(errors::str_error(EARG));
            return EARG;
        }
        IO::outl("\nUsage: \n"
                 "mpwd [-h|--help] print current directory \n"
                 "[-h|--help] print this message\n");

        return 0;
    }

    IO::outl(util::pwd());

    return 0;
}