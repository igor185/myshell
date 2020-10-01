#include <fcntl.h>
#include <unistd.h>
#include <string>

#include "IO/IO.hpp"

int IO::my_open(const char *file_name) {
    int fd = open(file_name, O_RDONLY);

    if (fd == -1) {
        if (errno == EINTR) {
            return my_open(file_name);
        } else {
            exit(EXIT_FAILURE);
        }
    }

    return fd;
}

ssize_t IO::my_read(int fd, char *buf, ssize_t b_size) {
    ssize_t b_read = read(fd, buf, b_size);

    if (b_read == -1) {
        if (errno == EINTR) {
            return my_read(fd, buf, b_size);
        } else {
            exit(EXIT_FAILURE);
        }
    }

    return b_read;
}

ssize_t IO::my_write(int fd, char *buf, ssize_t b_size, bool print_hex) {
    if (print_hex) {
        char hexed_buffer[BUF_SIZE * 4];
        ssize_t buf_position = 0;
        for (ssize_t i = 0; i < b_size; ++i, ++buf_position)
            if (!isprint(buf[i]) && !isspace(buf[i])) {
                sprintf(&hexed_buffer[buf_position], "\\x%02X", (unsigned char) buf[i]);
                buf_position += 3;
            } else
                hexed_buffer[buf_position] = buf[i];
        buf = hexed_buffer;
        b_size = buf_position;

    }
    ssize_t b_written = write(fd, buf, b_size);

    if (b_written == -1) {
        if (errno == EINTR) {
            return my_write(fd, buf, b_size, false);
        } else {
            exit(EXIT_FAILURE);
        }
    }
    return b_written;
}

int IO::my_close(int fd) {
    int status = close(fd);

    if (status == -1) {
        if (errno == EINTR) {
            return my_close(fd);
        } else {
            exit(EXIT_FAILURE);
        }
    }
    return status;
}