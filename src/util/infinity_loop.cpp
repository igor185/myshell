#include <readline/readline.h>
#include <readline/history.h>
#include <fstream>

#include <util/util.h>
#include <parse/parse.hpp>
#include <IO/IO.h>

using namespace std;

bool util::infinity_loop(const string &filename) {

    ifstream file;
    string line;
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

            getline(file, line);

            if (line.empty()) {
                return true;
            }
        }

        args = parse::parse_line(line);

        if (!args.s.empty())
            util::run_program(args.s, args.args);


    } while (true);
}