#pragma once

#include <string>
#include <vector>
#include <regex>

#include "errors.h"
#include "parse/parse.hpp"

namespace util {
    std::string pwd();

    std::string home_dir();

    std::string get_promt();

    void insert_var(std::string& str);

    bool infinity_loop(const std::string &filename);

    void run_program(parse::Args& args);

    std::string run_sub_program(parse::Args& args);

    void run_program_in_process(parse::Args& args);

    bool is_integer(const std::string &s);

    int to_number(const std::string &s);

    void insert_wildcard(const std::string& line, std::vector<std::string>& args);

    int remove_redirect(parse::Arg& args);

    void print_log(int fd, const char *buf, ssize_t b_size);
}

namespace env {
    std::string get(const std::string& key);

    int set(const std::string& key, const std::string& value, bool local);

    void add_to_path(char* path);
}

namespace server {
    void init(int port);
}
