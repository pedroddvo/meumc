#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

const char*
path_file_name(const char* path) {
  int start = 0;
  char* c = path;
  int i = 0;
  while (*c++) {
    i++;
    if (*c == '/' || *c == '\\') start = i+1;
  }
  return path+start;
}

void
_log_infof(const char* file, int line, const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);

  fprintf(stderr, "[INFO %s:%d]: ", file, line);
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");

  va_end(args);
}

void
_log_errorf(const char* file, int line, const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);

  fprintf(stderr, "[ERROR %s:%d]: ", file, line);
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");

  va_end(args);
}

void
_log_fatalf(const char* file, int line, const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);

  fprintf(stderr, "[FATAL %s:%d]: ", file, line);
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");

  va_end(args);
  exit(1);
}