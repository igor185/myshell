#include <util/util.h>

bool util::is_integer(const std::string & s){
    return std::regex_match(s, std::regex("[0-9]+"));
}

int util::to_number(const std::string & s){
    return std::stoi(s);
}

void util::insert_var(std::string& str){
    size_t index = str.find('$');
    if (index != std::string::npos) {
        str = str.substr(0, index) + env::get(str.substr(index + 1));
    }
}