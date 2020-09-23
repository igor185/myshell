#include <string>
#include <vector>

#include "errors.h"

namespace util {
    std::string pwd();

    std::string home_dir();

    std::string get_promt();

    void insert_var(std::string& str);

    void infinity_loop(const std::string &filename);

    void run_program(const std::string &name, std::vector<std::string> &args);
}

namespace env {
    const char* get(const std::string& key);

    void set(const std::string& key, std::string& value);

    void add_to_path(char* path);
}
