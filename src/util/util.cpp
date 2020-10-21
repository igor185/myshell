#include <util/util.h>
#include <fcntl.h>
#include <IO/IO.h>

bool util::is_integer(const std::string &s) {
    return std::regex_match(s, std::regex("[0-9]+"));
}

int util::to_number(const std::string &s) {
    return std::stoi(s);
}

void util::insert_var(std::string &str) {
    size_t index = str.find('$');
    if (index != std::string::npos) {
        str = str.substr(0, index) + env::get(str.substr(index + 1));
    }
}

int open_file(const std::string &name) {
    int filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                    S_IROTH | S_IWOTH; /* rw-rw-rw- */
    int fd = open(name.c_str(), O_CREAT | O_RDWR, filePerms);

    if (fd == -1) {
        if (errno == EINTR) {
            return open_file(name);
        }
        IO::err(std::strerror(errno));
        errors::set_error(ENKNOWN);
        return fd;
    }

    return fd;
}

int util::remove_redirect(parse::Arg &args) {
    std::vector<std::string> tokens;
    std::string token;
    for (size_t i = 0; i < args.args.size(); i++) {
        token = args.args[i];
        if (token == ">") {
            if (i + 1 != args.args.size()) {
                args.ofd = open_file(args.args[i + 1]);
                ++i;
            } else {
                IO::err("Unexpected token");
                errors::set_error(ENKNOWN);
                return -1;
            }
        } else if (token == "2>") {
            if (i + 1 != args.args.size()) {
                args.efd = open_file(args.args[i + 1]);
                ++i;
            } else {
                IO::err("Unexpected token");
                errors::set_error(ENKNOWN);
                return -1;
            }
        } else if (token == "2>&1") {
            args.efd = args.ofd;
        } else if (token == "&>") {
            if (i + 1 != args.args.size()) {
                int fd = open_file(args.args[i + 1]);
                args.ofd = fd;
                args.efd = fd;
                ++i;
            } else {
                IO::err("Unexpected token");
                errors::set_error(ENKNOWN);
                return -1;
            }
        }else if(token == "<"){
            if (i + 1 != args.args.size()) {
                args.ifd = open_file(args.args[i + 1]);
                ++i;
            } else {
                IO::err("Unexpected token");
                errors::set_error(ENKNOWN);
                return -1;
            }
        } else {
            tokens.push_back(token);
        }
    }
    args.args = tokens;
    return 0;
}