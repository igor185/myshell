#include <string>
#include <vector>
#include <zconf.h>

#include <parse/parse.hpp>
#include <util/util.h>
#include <IO/IO.h>

parse::Args parse::parse_line(std::string &line) {
    size_t index = 0;
    parse::Args args = {{{{}, STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO}}, true};
    std::vector<std::string> arg = {};

    line = line.substr(0, line.find('#', 0));

    std::stringstream ss(line);
    std::string s;

    while (ss >> s && !s.empty()) {
        size_t index_str = s.find("$(");
        if (index_str != std::string::npos) {
            size_t last_index = s.find_last_of(')');
            if (last_index == std::string::npos) {
                errors::set_error(EINCCOMAND);
                IO::err(errors::str_error(EINCCOMAND));
                return {};
            }
            std::string sub_command = s.substr(index_str + 2, last_index - index_str - 2);
            parse::Args sub_args = parse_line(sub_command);

            sub_command = util::run_sub_program(sub_args);

            if (errors::get_error()) {
                return {};
            }

            s = s.substr(0, index_str) + sub_command + s.substr(last_index + 1);
        }

        if (s == "|") {
            args.args[index].args = arg;
            arg = {};

            args.args.push_back({{}, STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO});
            index++;

            ss >> s;

            if(s.empty()){
                break;
            }
        }
        util::insert_var(s);

        util::insert_wildcard(s, arg);
    }
    if (!arg.empty() && arg[arg.size() - 1] == "&") {
        arg.pop_back();
        args.in_current_process = false;
    }

    args.args[index].args = arg;

    for (auto &ar: args.args) {
        if (util::remove_redirect(ar)) {
            return {};
        }
    }


    return args;
}