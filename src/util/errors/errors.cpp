#include "util/errors.h"

int error_status = 0;

std::string errors::str_error(int merrno) {
    switch (merrno) {
        case EARG:
            return "Incorrect arguments";
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
