#include "rio.h"

#include <stdlib.h>

#include "errno.h"


ssize_t rio_read(int fd, char *buf, size_t n) {


}

rio_buf_type *rio_buffer_init(int fd, size_t buf_size){
  rio_buf_type *rio_buf = (rio_buf_type*)malloc(sizeof(rio_buf_type));
  rio_buf->rio_fd = fd;
  rio_buf->rio_buffer = (char*)malloc(sizeof(char)*buf_size);
  rio_buf->rio_buffer_ptr = rio_buf->rio_buffer;
  rio_buf->rio_bytes_left = buf_size;
  return rio_buf;
}

void rio_buffer_release(rio_buf_type *rio_buffer) {
  rio_buffer->rio_buffer_ptr = NULL;
  free(rio_buffer->rio_buffer);
}

ssize_t rio_readn(int fd, void *buffer, size_t n) {
  size_t bytes_left = n;
  ssize_t bytes_read;
  char *buf = buffer;

  // 从fd中读取内容到buffer中
  while (bytes_left > 0) {
    if ((bytes_read = read(fd, buf, bytes_left)) < 0) {
      if (errno == EINTR) {
        bytes_read = 0;
      } else {
        return -1;
      }
    } else if (bytes_read == 0) {
      break;
    }
    bytes_left -= bytes_read;
    buf += bytes_read;
  }
  // 也许调用者只想读取一部分文件
  return n - bytes_left;
}

size_t rio_writen(int fd, void *buffer, size_t n) {
  size_t bytes_left = n;
  ssize_t bytes_written;
  char *buf = buffer;

  // 从buffer中写入fd
  while (bytes_left > 0) {
    if ((bytes_written = write(fd, buf, bytes_left)) < 0) {
      if (errno == EINTR) {
        bytes_written = 0;
      } else {
        return -1;
      }
    }
    bytes_left -= bytes_written;
    buf += bytes_written;
  }
  // 写文件就是写了n个byte 不存在写了n byte中的一部分的情况
  return n;
}