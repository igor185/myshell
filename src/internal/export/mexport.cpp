#include <string>

#include <internal/internal.hpp>
#include <util/util.h>


int internal::mexport(std::vector<std::string> &args) {
    if (args.empty()) {
        return errors::set_inc_args();
    }
    std::string line = args[0];

    size_t index = line.find('=');
    std::string value = env::get(line);

    if (index == std::string::npos) {
        if(!value.empty()){
            env::set(line, value, false);
            return 0;
        }
        return errors::set_inc_args();
    }

    env::set(line.substr(0, index), line.substr(index + 1), false);

    return 0;
}