#include <cstdlib>
#include <climits>
#include <libgen.h>

#include <util/util.h>

using namespace std;

const char* env::get(const string& key) {
    char* value = getenv(key.c_str());
    if(value == nullptr)
        return "";
    return value;
}

void env::set(const std::string& key, std::string &value) {
    setenv(key.c_str(), value.c_str(), 1);
}

void env::add_to_path(char* path_to_bin){
    char path[PATH_MAX];

    string path_var = env::get("PATH");
    path_var += + ":" + string(realpath(dirname(path_to_bin), path)) + "/external";

    env::set("PATH", path_var);
}

void util::insert_var(std::string& str){
    size_t index = str.find('$');
    if (index != std::string::npos) {
        str = str.substr(0, index) + env::get(str.substr(index + 1));
    }
}