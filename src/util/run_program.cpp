#include <unistd.h>
#include <wait.h>
#include <cstring>

#include <internal/internal.hpp>
#include <util/util.h>
#include <IO/IO.h>

void execute(const std::string &name, std::vector<std::string> &arg_parsed) {
    std::vector<const char *> args(arg_parsed.size() + 2);
    int i = 0;
    args[i++] = name.c_str();
    for (const auto &arg: arg_parsed)
        args[i++] = arg.c_str();

    args[i++] = nullptr;

    execvp(name.c_str(), const_cast<char *const *>(args.data()));


    errors::set_error(ENKNOWN);
    IO::err(strerror(errno));

    exit(EXIT_FAILURE);
}

void util::run_program(const std::string &name, std::vector<std::string> &arg_parsed) {

    if (!internal::run_internal_program(name, arg_parsed)) {

        pid_t pid = fork();

        if (pid == -1) {
            errors::set_error(ENFORK);
            IO::err(errors::str_error(ENFORK));
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            errors::set_error(ENKNOWN);
        } else {
            execute(name, arg_parsed);
        }

    }
}