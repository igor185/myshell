#include <internal/internal.hpp>
#include <IO/IO.h>

void print_help(){
    IO::outl("\nUsage: \n mecho [-h|--help] [text|$<var_name>] [text|$<var_name>]  [text|$<var_name>] ... \n"
             "[-h|--help] print this message \n"
             "[text|$<var_name>] - some text or if it start with $ will print from env variables");
};

int internal::mecho(std::vector<std::string> &args) {

    for(auto & arg : args){
        if(arg == "-h" || arg == "--help"){
            print_help();
            return 0;
        }
    }

    for(size_t i = 0; i + 1 < args.size(); i++){
        IO::out(args[i] + " ");
    }

    if(!args.empty())
        IO::out(args[args.size() - 1]);
    IO::outl("");

    return 0;
}