#include <string>

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
    } else if (name == "mexport") {
        return mexport(args);
    } else if (name == "mcd") {
        return mcd(args);
    } else if (name == "merrno") {
        return merrno(args);
    } else if (name == ".") {
        return mdot(args);
    } else if (name.find('=') != std::string::npos) {
        return add_local_var({name});
    } else {
        return -1;
    }
}

bool internal::run_internal_program(const std::string &name, std::vector<std::string> &args) {
    int status = run(name, args);

    if (status != -1) {
        errors::set_error(status);
        return true;
    }

    return false;
}