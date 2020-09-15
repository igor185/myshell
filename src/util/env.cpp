#include <cstdlib>
#include <climits>
#include <libgen.h>

#include <util/util.hpp>

using namespace std;
const char* env::get(const string& key) {
    char* value = getenv(key.c_str());
    if(value == nullptr)
        return "";
    return value;
}

void env::set(std::string key, std::string &value) {
    setenv(key.c_str(), value.c_str(), 1);
}

void env::add_to_path(char* path_to_bin){
    char path[PATH_MAX];

    string path_var = env::get("PATH");
    path_var += + ":" + string(realpath(dirname(path_to_bin), path)) + "/external";

    env::set("PATH", path_var);
}