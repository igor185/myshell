#include "unistd.h"

#include "parse/parse.hpp"
#include "IO/IO.hpp"

void cat(const parse::Args &parsed_args) {
    std::vector<int> fds;

    for (auto &file: parsed_args.file_names) {
        fds.push_back(IO::my_open(file.c_str()));
    }
    
    for (auto &i: fds) {
        ssize_t b_used = 1;
        while (b_used > 0) {
            b_used = IO::my_read(i, buffer, BUF_SIZE);
            b_used = IO::my_write(STDOUT_FILENO, buffer, b_used, parsed_args.A);
        }
    }

    for(auto &file: fds){
        IO::my_close(file);
    }
}


int main(int argc, char **argv) {

    cat(parse::parse_ags(argc, argv));

    return EXIT_SUCCESS;
}
