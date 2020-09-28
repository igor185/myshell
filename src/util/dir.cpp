#include <unistd.h>
#include <wordexp.h>

#include <util/util.h>

using namespace std;

string util::pwd() {
    return get_current_dir_name();
}

string home;

string util::home_dir() {
    if (home.empty())
        home = env::get("HOME");

    return home;
}

string replace_home(const string &p) {
    string home_path = util::home_dir();
    size_t index = p.find(home_path);

    if (index == string::npos)
        return p;

    return p.substr(0, index) + "~" + p.substr(index + home_path.size());
}

string util::get_promt() {
    return replace_home(util::pwd()).append("$ ");
}

void util::insert_wildcard(const std::string &line, std::vector<std::string> &args) {
    wordexp_t p;

    wordexp(line.c_str(), &p, 0);

    for (size_t i = 0; i < p.we_wordc; i++)
        args.emplace_back(p.we_wordv[i]);

    wordfree(&p);
}