#include <unistd.h>
#include <wait.h>
#include <cstring>

#include <internal/internal.hpp>
#include <util/util.h>
#include <IO/IO.h>

using namespace std;


void execute(const string &name, vector<string> &arg_parsed){
    vector<const char *> args(arg_parsed.size() + 2);
    int i = 0;
    args[i++] = name.c_str();
    for (const auto &arg: arg_parsed)
        args[i++] = arg.c_str();

    args[i++] = nullptr;

    execvp(name.c_str(), const_cast<char* const*>(args.data()));


    errors::set_error(ENKNOWN);
    IO::err(strerror(errno));

    exit(EXIT_FAILURE);
}

void util::run_program(const string &name, vector<string> &arg_parsed) {

    if (!internal::run_internal_program(name, arg_parsed)) {

        pid_t pid = fork();

        if (pid == -1) {
            IO::err( "Failed to fork()");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            // TODO Add to merrno status for success and error
        } else {
            execute(name, arg_parsed);
        }
    }
}