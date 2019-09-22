#ifndef H862DCCEC_B916_4720_8F8B_AE282F9DA5B9
#define H862DCCEC_B916_4720_8F8B_AE282F9DA5B9

#include <string>
#include <typeinfo>

namespace cctest {

std::string getDemangledName(const std::type_info&);

template<typename T>
struct TypeString {
  static std::string value() {
    return getDemangledName(typeid(T));
  }
};

template<>
struct TypeString<std::string> {
  static std::string value() {
    return "std::string";
  }
};

} // namespace cctest

#endif
