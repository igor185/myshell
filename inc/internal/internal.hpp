#pragma once

#include <string>
#include <vector>

namespace internal {
    bool run_internal_program(std::vector<std::string> args, int in_fd, int out_fd, int err_fd);

    // without name
    int mpwd(std::vector<std::string>& args);

    int mexit(std::vector<std::string>& args);

    int mecho(std::vector<std::string>& args);

    int mexport(std::vector<std::string>& args);

    int mcd(std::vector<std::string>& args);

    int merrno(std::vector<std::string>& args);

    int mdot(std::vector<std::string>& args);

    int add_local_var(const std::vector<std::string>& args);
}