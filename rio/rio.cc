#include "rio.h"
#include "errno.h"
ssize_t rio_readn(int fd, void *buffer, size_t n) {
  size_t bytes_left = n;
  ssize_t bytes_read;
  char* buf = buffer;

  // 从fd中读取内容到buffer中
  while (bytes_left > 0) {
    if((bytes_read = read(fd, buf, bytes_left)) < 0) {
      if(errno == EINTR) {
        bytes_read = 0;
      }
      else {
        return -1;
      }
    }
    else if(bytes_read == 0){
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