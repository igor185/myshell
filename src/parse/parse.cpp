#include <string>
#include <vector>

#include <parse/parse.hpp>
#include <util/util.h>

parse::Args parse::parse_line(std::string& line) {
    Args args = {true, "", {} };
    std::vector<std::string> arg;

    line = line.substr(0, line.find('#', 0));

    std::stringstream ss(line);
    std::string s;

    ss >> s;
    args.s = s;

    while (ss >> s && !s.empty()) {

        util::insert_var(s);

        util::insert_wildcard(s, arg);

    }

    args.args = arg;

    return args;
}