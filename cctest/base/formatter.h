#ifndef H0437497C_F29A_4ACF_A546_5D531EFB1D76
#define H0437497C_F29A_4ACF_A546_5D531EFB1D76

#include <sstream>
#include "cctest/base/type_string.h"

namespace cctest {

///////////////////////////////////////////////////////
namespace details {

std::string toPointerString(void*);
std::string toBufferString(void *buf, size_t size);

} // namespace details

///////////////////////////////////////////////////////
template<typename T>
std::string toString(T val) {
  return details::toBufferString((void*) &val, sizeof(val));
}

///////////////////////////////////////////////////////
std::string toString(std::string s);
std::string toString(char *s);
std::string toString(const char *s);
std::string toString(float f);
std::string toString(double d);
std::string toString(bool b);
std::string toString(char c);
std::string toString(unsigned char c);
std::string toString(short s);
std::string toString(unsigned short s);
std::string toString(int i);
std::string toString(unsigned int i);
std::string toString(long l);
std::string toString(unsigned long l);

std::string toString(long long ll);
std::string toString(unsigned long long ll);

///////////////////////////////////////////////////////
template<typename T>
std::string toString(T *p) {
  return details::toPointerString((void*) p);
}

///////////////////////////////////////////////////////
template<typename T>
std::string toString(const T *s) {
  return toString(const_cast<T*>(s));
}

/////////////////////////////////////////////////////////////////
template<typename T>
std::string toTypeAndValueString(const T &val) {
  std::stringstream ss;
  ss << "(" << TypeString<T>::value() << ")" << toString(val);
  return ss.str();
}

} // namespace cctest

#endif
