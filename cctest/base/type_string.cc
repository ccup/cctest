#include "cctest/base/type_string.h"

#if (__GNUC__ && __GNUC__ > 3)

#include <cxxabi.h>
#include <stdlib.h>

struct DemangledName {
  DemangledName(const std::type_info& type) : name(demangle(type)) {
  }

  ~DemangledName() {
    ::free(name);
  }

  std::string getName() const {
    return name;
  }

private:
  char* demangle(const std::type_info& type) {
    int status;
    return abi::__cxa_demangle(type.name(), 0, 0, &status);
  }

private:
  char* name;
};

#else

struct DemangledName() {
  DemangledName(const std::type_info& type) : type(type) {
  }

  std::string getName() const {
    return type.name();
  }

private:
  const std::type_info& type;
};

#endif

namespace cctest {

std::string getDemangledName(const std::type_info &type) {
  return DemangledName(type).getName();
}

} // namespace cctest
