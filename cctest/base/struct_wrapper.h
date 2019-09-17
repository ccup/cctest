#ifndef H26412F06_56BF_47FD_AD4F_6636917F7861
#define H26412F06_56BF_47FD_AD4F_6636917F7861

namespace cctest {

template<typename From, typename To>
struct StructWrapper: protected From {

  static const To& by(const From& from) {
    static_assert(sizeof(From) == sizeof(To), "");
    return (const To&) from;
  }

  static To& by(From& from) {
    static_assert(sizeof(From) == sizeof(To), "");
    return (To&) from;
  }
};

#define CCTEST_STRUCT_WRAPPER(To, From) \
  struct To : cctest::StructWrapper<From, To>


} // namespace cctest

#endif
