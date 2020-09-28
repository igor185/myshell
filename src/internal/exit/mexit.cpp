#include <internal/internal.hpp>
#include <util/util.h>
#include <IO/IO.h>

int internal::mexit(std::vector<std::string> &args) {
    bool is_print_help = false;
    int status = EXIT_SUCCESS;

    for(const auto& i: args){
        if(i == "-h" || i == "--help"){
            is_print_help = true;
        } else if(util::is_integer(i)){
            status = util::to_number(i);
        } else{
            errors::set_error(EARG);
            IO::err(errors::str_error(EARG));
            exit(EXIT_FAILURE);
        }
    }

    if(is_print_help){
        IO::outl("\nUsage: \n mexit [-h|--help] [status]"
                 "exit program \n"
                 "[-h|--help] print this message \n"
                 "[status] status of exit, EXIT_SUCCESS by default");
        return 0;
    }
    exit(status);
}