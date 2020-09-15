#include <readline/readline.h>
#include <readline/history.h>
#include <fstream>

#include <util/util.hpp>
#include <parse/parse.hpp>

void util::infinity_loop(const std::string &filename) {
    bool from_file = !filename.empty();
    std::ifstream file;
    std::string s;
    parse::Args args;

    do {
        s.clear();

        if (!from_file) {
            s = readline(util::replace_home(util::pwd()).append("$ ").c_str());

            if (!s.empty())
                add_history(s.data());
        } else {
            if (!file.is_open()) {
                file.open(filename);
            }

            std::getline(file, s);
            if (s.empty()) {
                return;
            }
        }

        args = parse::parse_line(s);

        if (!args.s.empty())
            util::run_program(args.s, args.args);


    } while (true);
}