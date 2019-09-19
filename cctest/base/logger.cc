#include "cctest/base/logger.h"
#include <stdlib.h>

namespace cctest {

LogStream::LogStream(const char* file, int line, LogLevel level)
  : file(file), line(line), level(level) {
}

LogStream::~LogStream() {
  fprintf(stderr, "[%c %s:%d] %s\n", "IWEF"[level], file, line, str().c_str());
}

} // namespace cctest
