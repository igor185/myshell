#include <vector>
#include <string>

#include <internal/internal.hpp>
#include <util/util.h>

using namespace std;

int internal::mdot(std::vector<std::string>& args){
    if(args.empty()){
        return errors::set_inc_args();
    }

    size_t index = args[0].find_last_of('.');

    if(index == string::npos || args[0].substr(index+1) != "msh"){
        return errors::set_inc_args();
    }

    if(!util::infinity_loop(args[0])){
        return errors::get_error();
    }
    return 0;
}