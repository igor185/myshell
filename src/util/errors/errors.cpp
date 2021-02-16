#include <util/errors.h>
#include <IO/IO.h>

int error_status = 0;

std::string errors::str_error(int merrno) {
    switch (merrno) {
        case 0:
            return "OK";
        case EARG:
            return "Incorrect arguments";
        case ENOFILEORDIR:
            return "File or directory is not exists";
        case ENOACESS:
            return "You don't have access";
        case ENOTADIR:
            return "Not a directory";
        case ENFORK:
            return "Failed to fork()";
        case EMEMORY:
            return "Memory is over";
        case EINCCOMAND:
            return "Incorrect command";
        case EDUP:
            return "Cannot dup 2";
        case EWAIT:
            return "Forked process return error";
        case ECRPIPE:
            return "Cannot create pipe";
        case ENKNOWN:
        default:
            return "Unknown error";
    }
}

void errors::set_error(int merrno) {
    error_status = merrno;
}

int errors::get_error() {
    return error_status;
}

int errors::set_inc_args(){
    errors::set_error(EARG);
    IO::err(errors::str_error(EARG));

    return EARG;
}

void errors::reset_error() {
    error_status = 0;
}
