#include <unistd.h>

#include <util/util.hpp>

using namespace std;

string home;

char* util::pwd() {
    return get_current_dir_name();
}

string util::home_dir() {
    if(home.empty())
        home = env::get("HOME");

    return home;
}

string util::replace_home(char* p) {
    string path = p;
    string home_path = home_dir();
    size_t index = path.find(home_path);

    if(index == string::npos)
        return p;

    path = path.substr(0, index) + "~" + path.substr(index+home_path.size());

    return path;
}