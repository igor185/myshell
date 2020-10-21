#include <unistd.h>
#include <wait.h>
#include <cstring>

#include <internal/internal.hpp>
#include <util/util.h>
#include <IO/IO.h>
#include <parse/parse.hpp>

void dup_for_exec(int fd1, int fd2){
    if (fd1 != fd2) {
        if (dup2(fd1, fd2) == -1) {
            IO::err("cannot dup2");
            exit(EXIT_FAILURE);
        };
    }
}

void my_close(int fd){
    if(close(fd) == -1){
        errors::set_error(ECLOSE);
        IO::err(errors::str_error(ECLOSE));
    }
}

void close_fds(int fd_in, int fd_out, int fd_err){
    if (fd_in != STDIN_FILENO)
        my_close(fd_in);
    if (fd_out != STDOUT_FILENO)
        my_close(fd_out);
    if (fd_err != STDERR_FILENO)
        my_close(fd_err);
}

void execute(std::vector<std::string> &arg_parsed, int in_fd, int out_fd, int err_fd) {
    dup_for_exec(in_fd, STDIN_FILENO);
    dup_for_exec(out_fd, STDOUT_FILENO);
    dup_for_exec(err_fd, STDERR_FILENO);

    std::vector<const char *> args(arg_parsed.size() + 1);
    int i = 0;
    for (const auto &arg: arg_parsed)
        args[i++] = arg.c_str();
    args[i++] = nullptr;
    execvp(args[0], const_cast<char *const *>(args.data()));

    errors::set_error(ENKNOWN);
    IO::err(strerror(errno));

    exit(EXIT_FAILURE);
}

void util::run_program(parse::Args &args) {
    int pipes[2] = {-1, -1};
    for (size_t i = 0; i < args.args.size(); i++) {
        bool last = (i + 1 == args.args.size());
        if (!last) {
            if (pipe(pipes) == -1) {
                errors::set_error(ECRPIPE);
                IO::err(errors::str_error(ECRPIPE));
            }
            if (args.args[i].ofd == STDOUT_FILENO) {
                args.args[i].ofd = pipes[1];
            } else {
                close(pipes[1]);
            }

            if (args.args[i + 1].ifd == STDIN_FILENO) {
                args.args[i + 1].ifd = pipes[0];
            } else {
                close(pipes[0]);
            }
        }
        if (!internal::run_internal_program(args.args[i].args, args.args[i].ifd, args.args[i].ofd, args.args[i].efd)) {

            pid_t pid = fork();

            if (pid == -1) {
                errors::set_error(ENFORK);
                IO::err(errors::str_error(ENFORK));
            } else if (pid > 0) {
                int status;
                waitpid(pid, &status, 0);

                close_fds(args.args[i].ifd, args.args[i].ofd, args.args[i].efd);

            } else {
                execute(args.args[i].args, args.args[i].ifd, args.args[i].ofd, args.args[i].efd);
            }
        } else {
            close_fds(args.args[i].ifd, args.args[i].ofd, args.args[i].efd);
        }
    }
}

std::string util::run_sub_program(parse::Args &args) {
    if(args.args.empty() || args.args[0].args.empty())
        return "";

    FILE *tmp = tmpfile();
    std::string res;
    pid_t pid = fork();

    if (pid == -1) {
        errors::set_error(ENFORK);
        IO::err(errors::str_error(ENFORK));
        return "";
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);

        fflush(tmp);
        rewind(tmp);
        const size_t buffer_size = 4096;
        auto *buf = new char[buffer_size + 1];
        while (fread(buf, sizeof(char), buffer_size, tmp) > 0) {
            if (ferror(tmp) && !feof(tmp)) {
                errors::set_error(ENKNOWN);
                IO::err(errors::str_error(ENKNOWN));
                delete[] buf;
                return "";
            } else {
                res += buf;
            }
        }
        delete[] buf;
        return res;
    } else {
        errors::reset_error();
        if(dup2(fileno(tmp), STDOUT_FILENO) == -1){
            errors::set_error(EDUP);
            IO::err(errors::str_error(EDUP));
            exit(EXIT_FAILURE);
        }

        run_program(args);

        if(!errors::get_error())
            exit(EXIT_SUCCESS);
        else
            exit(EXIT_FAILURE);
    }
}

void util::run_program_in_process(parse::Args &args) {
    pid_t pid = fork();

    if (pid == -1) {
        errors::set_error(ENFORK);
        IO::err(errors::str_error(ENFORK));
    } else if (pid > 0) {
        // TODO in parent process
    } else {
        // TODO close 0, 1, 2 fd
        close(0);
        close(1);
        close(2);

        run_program_in_process(args);
    }
}