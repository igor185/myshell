#include <string>

#include <internal/internal.hpp>
#include <util/util.h>


int internal::mexport(std::vector<std::string> &args) {
    if (args.empty()) {
        return errors::set_inc_args();
    }
    std::string line = args[0];

    size_t index = line.find('=');

    if (index == std::string::npos) {
        return errors::set_inc_args();
    }

    env::set(line.substr(0, index), line.substr(index + 1), 0);

    return 0;
}