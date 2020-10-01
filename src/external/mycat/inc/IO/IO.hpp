#ifndef MYCAT_IO_HPP
#define MYCAT_IO_HPP

// 10Mb
#define BUF_SIZE 1048576
char buffer[BUF_SIZE];


namespace IO {

    int my_open(const char *file_name);

    ssize_t my_read(int fd, char *buffer, ssize_t b_size);

    ssize_t my_write(int fd, char *buf, ssize_t b_size, bool print_hex);

    int my_close(int fd);
}

#endif

