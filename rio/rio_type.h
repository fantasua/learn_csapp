#define RIO_BUF_SIZE 4096
#pragma once
typedef struct {
  int rio_fd;            // 对应的fd
  int rio_bytes_left;    // 缓冲区内尚未读取的字节数
  char *rio_buffer_ptr;  // 当前缓冲区指针位置
  char *rio_buffer;      // 缓冲区空间
} rio_buf_type;