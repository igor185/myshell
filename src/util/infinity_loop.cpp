#include <readline/readline.h>
#include <readline/history.h>
#include <fstream>

#include <util/util.h>
#include <parse/parse.hpp>
#include <IO/IO.h>

bool util::infinity_loop(const std::string &filename) {

    std::ifstream file;
    std::string line;
    parse::Args args;

    bool from_file = !filename.empty();

    do {
        line.clear();

        if (!from_file) {
            // from stdin
            line = readline(util::get_promt().c_str());

            if (!line.empty())
                add_history(line.data());
        } else {
            // from file
            if (!file.is_open()) {
                file.open(filename);

                if (!file.is_open()) {
                    IO::err("File is not exists: " + filename);
                    errors::set_error(ENOFILEORDIR);

                    return false;
                }
            }
            if (file.eof()) {
                return true;
            }

            getline(file, line);

            if(line.empty()){
                continue;
            }
        }

        args = parse::parse_line(line);

        if (!args.args.empty() && !args.args[0].args.empty()) {
            if(args.in_current_process) {
                util::run_program(args);
            } else
                util::run_program_in_process(args);
        }


    } while (true);
}