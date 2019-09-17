#ifndef H8CE6A8CC_07AF_4BE2_98DA_87E4FA17C17D
#define H8CE6A8CC_07AF_4BE2_98DA_87E4FA17C17D

namespace cctest {

template<typename T>
struct Singleton {
  static T& inst() {
    static T inst;
    return inst;
  }

protected:
  Singleton() {}
};

#define CCTEST_SINGLETON(type) \
  struct type : cctest::Singleton<type>

#define CCTEST_GENERIC_SINGLETON(type, ...) \
  struct type : cctest::Singleton<type<__VA_ARGS__>>

} // namespace cctest

#endif
