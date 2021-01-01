#include <unistd.h>

// robust io functions

// read from fd with user space buffer



// read n bytes from fd with no user space buffer
ssize_t rio_readn(int fd, void *buffer, size_t n);

// write n bytes to fd with no user space buffer
size_t rio_writen(int fd, void *buffer, size_t n);