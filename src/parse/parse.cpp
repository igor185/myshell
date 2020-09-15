#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <parse/parse.hpp>
#include <util/util.hpp>

parse::Args parse::parse_line(std::string& line) {
    Args args = {true, "", {} };
    std::vector<std::string> arg;

    line = line.substr(0, line.find('#', 0));

    std::stringstream ss(line);
    std::string s;

    ss >> s;

    args.s = s;

    while (ss >> s && !s.empty()) {
        if(s[0] == '$'){
            std::cout << s.substr(1) << std::endl;
            s = env::get(s.substr(1));
        }
        arg.push_back(s);
    }

    args.args = arg;

    return args;
}