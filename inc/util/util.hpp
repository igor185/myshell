#include <string>
#include <vector>
#include "errors.h"

namespace util {
    char* pwd();
    std::string home_dir();
    std::string replace_home(char* p);

    void infinity_loop(const std::string &filename);

    void run_program(const std::string &name, std::vector<std::string> &args);
}

namespace env {
    const char* get(const std::string& key);

    void set(std::string key, std::string& value);

    void add_to_path(char* path);
}
