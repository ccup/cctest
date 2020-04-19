#ifndef H8238C8F9_6F1E_4E39_A06F_2147D2BAC688
#define H8238C8F9_6F1E_4E39_A06F_2147D2BAC688

namespace cctest {

struct Hook {
  virtual void invoke() = 0;
  virtual ~Hook() {}
};

struct BeforeHook : Hook {
  BeforeHook();
};

struct AfterHook : Hook {
  AfterHook();
};

} // namespace cctest

#endif /* H8238C8F9_6F1E_4E39_A06F_2147D2BAC688 */
