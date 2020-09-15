#include <internal/internal.hpp>
#include <util/util.hpp>
#include <iostream>
using namespace internal;

int run(const std::string &name, std::vector<std::string> &args) {
    if (name == "mpwd") {
        return mpwd(args);
    }else if(name == "mexit"){
        return mexit(args);
    }else if(name == "mecho"){
        return mecho(args);
//    }else if(name == "mexport"){
//        mexport(args);
    }else if(name == "mcd"){
        return mcd(args);
    }else if(name == "merrno"){
        return merrno(args);

    } else {
        return -1;
    }
}

bool internal::run_internal_program(const std::string &name, std::vector<std::string> &args){
    int status = run(name, args);

    if(status != -1){
        errors::str_error(status);
        return true;
    }

    return false;
}