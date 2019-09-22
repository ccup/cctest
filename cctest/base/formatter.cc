#include "cctest/base/formatter.h"

#include <sstream>
#include <algorithm>

namespace cctest {

namespace {

template<typename T>
inline std::string toValStr(T val) {
  std::stringstream ss;
  ss << val;
  return ss.str();
}

inline std::string toValStr(char val) {
  return toValStr((int) val);
}

inline std::string toValStr(signed char val) {
  return toValStr((int) val);
}

inline std::string toValStr(unsigned char val) {
  return toValStr((unsigned int) val);
}

template<typename T>
inline std::string toHexStr(T val) {
  std::stringstream ss;
  ss.flags(std::ios::hex | std::ios::showbase);
  ss << val;
  return ss.str();
}

inline std::string toHexStr(char val) {
  return toHexStr((int) val & 0xFF);
}

inline std::string toHexStr(signed char val) {
  return toHexStr((int) val & 0xFF);
}

inline std::string toHexStr(unsigned char val) {
  return toHexStr((unsigned int) val & 0xFF);
}

inline std::string toHexStr(short val) {
  return toHexStr((unsigned int) val & 0xFFFF);
}

inline std::string toHexStr(int val) {
  return toHexStr((unsigned int) val & 0xFFFFFFFF);
}

inline std::string toFixedSizedHexStr(unsigned int i) {
  std::stringstream ss;
  ss.flags(std::ios::hex);
  ss.fill('0');
  ss.width(2);
  ss << i;
  return ss.str();
}

inline std::string toFixedSizedHexStr(unsigned char val) {
  return toFixedSizedHexStr((unsigned int) val & 0xFF);
}

template<typename T>
inline std::string toPCharStr(const T &s) {
  std::stringstream ss;
  s == 0 ? (ss << "NULL") : (ss << "\"" << s << "\"");
  return ss.str();
}

template<typename T>
inline std::string toHexAndDecStr(T val) {
  std::stringstream ss;
  ss << toHexStr(val) << "/" << toValStr(val);
  return ss.str();
}

} // namespace

namespace details {

std::string toPointerString(void *p) {
  if (p == 0)
    return "NULL";

  std::stringstream ss;

  ss << "0x";
  ss.flags(std::ios::hex);
  ss.fill('0');
  ss.width(8);
  ss << reinterpret_cast<unsigned long>(p);

  return ss.str();
}

std::string toBufferString(void *buf, size_t size) {
  std::stringstream ss;

  auto sz = std::min(size, size_t(4));
  auto p = (unsigned char*) buf;

  ss << "[";

  for (size_t i = 0; i < sz; i++) {
    ss << toFixedSizedHexStr(p[i]);
    if (i != sz - 1) {
      ss << " ";
    }
  }

  if (size > size_t(4)) {
    ss << " ...";
  }

  ss << "]";

  return ss.str();
}

} // namespace details

std::string toString(std::string s) {
  std::stringstream ss;
  ss << "\"" << s << "\"";
  return ss.str();
}

std::string toString(char *s) {
  return toPCharStr(s);
}

std::string toString(const char *s) {
  return toPCharStr(s);
}

std::string toString(bool b) {
  std::stringstream ss;
  ss << (b ? "true" : "false");
  return ss.str();
}

std::string toString(char c) {
  return toHexAndDecStr(c);
}

std::string toString(signed char c) {
  return toHexAndDecStr(c);
}

std::string toString(unsigned char c) {
  return toHexAndDecStr(c);
}

std::string toString(short s) {
  return toHexAndDecStr(s);
}

std::string toString(unsigned short s) {
  return toHexAndDecStr(s);
}

std::string toString(int i) {
  return toHexAndDecStr(i);
}

std::string toString(unsigned int i) {
  return toHexAndDecStr(i);
}

std::string toString(long l) {
  return toHexAndDecStr(l);
}

std::string toString(unsigned long l) {
  return toHexAndDecStr(l);
}

std::string toString(long long ll) {
  return toHexAndDecStr(ll);
}

std::string toString(unsigned long long ll) {
  return toHexAndDecStr(ll);
}

std::string toString(float f) {
  return toValStr(f);
}

std::string toString(double f) {
  return toValStr(f);
}

std::string toTypeAndValueString(std::nullptr_t p) {
  std::stringstream ss;
  ss << "(std::nullptr_t)" << toString((void*)p);
  return ss.str();
}

} // namespace cctest
