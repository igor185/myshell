#include <string>

#include <internal/internal.hpp>
#include <util/util.h>
#include <zconf.h>

using namespace internal;

int run(std::vector<std::string> &args) {
    const std::string name = args[0];
    args.erase(args.begin(), args.begin() + 1);

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

int change_fd(int destination, int origin){
    if(origin != destination){
        int saved = dup(origin);
        dup2(destination, origin);
        return saved;
    }
    return -1;
}

void back_fd(int old, int curr){
    if(old != -1){
        dup2(old, curr);
        close(old);
    }
}
bool internal::run_internal_program(std::vector<std::string> args, int in_fd, int out_fd, int err_fd) {
    int saved_in = change_fd(in_fd, STDIN_FILENO), saved_out = change_fd(out_fd, STDOUT_FILENO), saved_err = change_fd(err_fd, STDERR_FILENO);

    int status = run(args);

    back_fd(saved_in, STDIN_FILENO);
    back_fd(saved_out, STDOUT_FILENO);
    back_fd(saved_err, STDERR_FILENO);

    if (status != -1) {
        errors::set_error(status);
        return true;
    }

    return false;
}