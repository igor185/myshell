#include <cstdlib>
#include <climits>
#include <libgen.h>
#include <unordered_map>

#include <util/util.h>
#include <IO/IO.h>


std::unordered_map<std::string, std::string> local_var;

std::string env::get(const std::string &key) {
    char *value = getenv(key.c_str());
    if (value == nullptr) {
        auto iter = local_var.find(key);
        if (iter != local_var.end()) {
            return iter->second;
        }
        return "";
    }
    return value;
}

int env::set(const std::string &key, const std::string &value, bool local) {
    if (local) {
        local_var[key] = value;
        return 0;
    }
    if (!setenv(key.c_str(), value.c_str(), 1)) {
        if (errno == ENOMEM) {
            return EMEMORY;
        } else {
            return ENKNOWN;
        }
    }

    if(local_var.find(key) != local_var.end()){
        local_var.erase(key);
    }

    return 0;
}

void env::add_to_path(char *path_to_bin) {
    char path[PATH_MAX];

    std::string path_var = env::get("PATH");
    path_var += ":" + std::string(realpath(dirname(path_to_bin), path)) + "/external";

    env::set("PATH", path_var, 0);
}