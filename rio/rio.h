#include <unistd.h>

#include "rio_type.h"

#pragma once

// robust io functions

// read from fd with user space buffer
ssize_t rio_read(int fd, char *buf, size_t n);


// init && release the rio_buffer
// init the rio_buffer
rio_buf_type *rio_buffer_init(int fd, size_t buf_size = RIO_BUF_SIZE);
// release the rio_buffer
void rio_buffer_release(rio_buf_type *rio_buffer);


// rio functions with no user space buffer
// read n bytes from fd with no user space buffer
ssize_t rio_readn(int fd, void *buffer, size_t n);

// write n bytes to fd with no user space buffer
size_t rio_writen(int fd, void *buffer, size_t n);