#ifndef HF2388CDE_6A93_42C7_9830_C63FFFAF973F
#define HF2388CDE_6A93_42C7_9830_C63FFFAF973F

namespace cctest {

struct NotMatcherTag {};
struct MatcherTag    {};

template <typename T>
struct MatcherTraits {
  using argument = T;
  using category = NotMatcherTag;
};

////////////////////////////////////////////////
#define CCTEST_MATCHER_TAG(matcher_t, arg_t)  \
template <>                                   \
struct MatcherTraits< matcher_t > {           \
  using argument = arg_t;                     \
  using category = MatcherTag;                \
}

////////////////////////////////////////////////
#define CCTEST_GENERIC_MATCHER_TAG(matcher_t) \
template <typename T>                         \
struct MatcherTraits< matcher_t<T> > {        \
  using argument = T;                         \
  using category = MatcherTag;                \
}

} // namespace cctest

#endif
