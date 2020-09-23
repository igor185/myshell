#include <internal/internal.hpp>
#include <IO/IO.h>

int internal::mecho(std::vector<std::string> &args) {
    // TODO help & args
    for(size_t i = 0; i + 1 < args.size(); i++){
        IO::out(args[i] + " ");
    }
    if(!args.empty())
        IO::out(args[args.size() - 1]);
    IO::outl("");

    return 0;
}