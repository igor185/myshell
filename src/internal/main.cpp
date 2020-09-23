#include <internal/internal.hpp>
#include <util/util.h>

using namespace internal;

int run(const std::string &name, std::vector<std::string> &args) {
    if (name == "mpwd") {
        return mpwd(args);
    } else if (name == "mexit") {
        return mexit(args);
    } else if (name == "mecho") {
        return mecho(args);
    }else if(name == "mexport"){
        return mexport(args);
    } else if (name == "mcd") {
        return mcd(args);
    } else if (name == "merrno") {
        return merrno(args);
    } else if (name == ".") {
        util::infinity_loop(args[0]); // TODO check args[0], check if it .msh, add exit status and move this logic
        return 0;
    } else {
        return -1;
    }
}

bool internal::run_internal_program(const std::string &name, std::vector<std::string> &args) {
    int status = run(name, args);

    if (status != -1) {
        errors::str_error(status);
        return true;
    }

    return false;
}