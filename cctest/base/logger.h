#ifndef HCDD2F687_B9B8_4E46_97C3_6C1723324D4E
#define HCDD2F687_B9B8_4E46_97C3_6C1723324D4E

#include <sstream>

namespace cctest {

struct LogStream : std::ostringstream {
  enum LogLevel {
    CCTEST_INFO,
    CCTEST_WARN,
    CCTEST_ERROR,
    CCTEST_FATAL,
  };

  LogStream(const char* file, int line, LogLevel level);
  ~LogStream();

private:
  void trace() const;

private:
  const char* file;
  int line;
  int level;
};

#define CCTEST_LOG_STREAM(level) \
  cctest::LogStream(__FILE__, __LINE__, cctest::LogStream::level)

#define CCTEST_INFO_LOG  CCTEST_LOG_STREAM(CCTEST_INFO)
#define CCTEST_WARN_LOG  CCTEST_LOG_STREAM(CCTEST_WARN)
#define CCTEST_ERR_LOG   CCTEST_LOG_STREAM(CCTEST_ERROR)
#define CCTEST_FATAL_LOG CCTEST_LOG_STREAM(CCTEST_FATAL)

} // namespace cctest

#endif
