#ifndef H69412324_8D5D_4E16_9ED9_1074F64BA585
#define H69412324_8D5D_4E16_9ED9_1074F64BA585

#include <exception>
#include <string>

namespace cctest {

struct AssertionError : std::exception {
  AssertionError(const std::string& src, const std::string& msg);
};


} // namespace cctest

#endif
