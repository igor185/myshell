#include <iostream>

#include "internal/internal.hpp"

int internal::mecho(std::vector<std::string> &args) {
    // TODO help & args
    for(size_t i = 0; i + 1 < args.size(); i++){
        std::cout << args[i] << " ";
    }
    if(args.size() >= 1)
        std::cout << args[args.size() - 1];
    std::cout << std::endl;

    return 0;
}