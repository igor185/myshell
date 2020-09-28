#ifndef ERRORS
#define ERRORS

#include <string>

#define ENKNOWN 1
#define EARG 2
#define ENOFILEORDIR 3
#define ENOACESS 4
#define ENOTADIR 5
#define ENFORK 6
#define EMEMORY 7

namespace errors {
    std::string str_error(int merrno);

    void set_error(int merrno);

    int get_error();

    int set_inc_args();
}

#endif