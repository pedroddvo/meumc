#if !defined(ERROR_H)
#define ERROR_H

// Returns the offset of a path until a file name
const char*
path_file_name(const char* path);

void
_log_infof(const char* file, int line, const char* fmt, ...);

void
_log_errorf(const char* file, int line, const char* fmt, ...);

void
_log_fatalf(const char* file, int line, const char* fmt, ...);

#define log_infof(fmt, ...) \
  _log_infof(__FILE__, __LINE__, fmt, __VA_ARGS__)

#define log_fatalf(fmt, ...) \
  _log_fatalf(__FILE__, __LINE__, fmt, __VA_ARGS__)

#define assert_fatalf(cond, fmt, ...) \
  if (!(cond)) _log_fatalf(__FILE__, __LINE__, fmt, __VA_ARGS__)

// #define log_infof(fmt, ...) \
//   _log_infof(fmt, __VA_ARGS__)

#endif // ERROR_H
