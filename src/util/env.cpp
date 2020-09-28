#include <cstdlib>
#include <climits>
#include <libgen.h>

#include <util/util.h>
#include <IO/IO.h>

using namespace std;

const char *env::get(const string &key) {
    char *value = getenv(key.c_str());
    if (value == nullptr)
        return "";
    return value;
}

int env::set(const std::string &key, const std::string &value) {
    if (!setenv(key.c_str(), value.c_str(), 1)) {
        if (errno == ENOMEM) {
            return EMEMORY;
        } else {
            return ENKNOWN;
        }
    }

    return 0;
}

void env::add_to_path(char *path_to_bin) {
    char path[PATH_MAX];

    string path_var = env::get("PATH");
    path_var += ":" + string(realpath(dirname(path_to_bin), path)) + "/external";

    env::set("PATH", path_var);
}