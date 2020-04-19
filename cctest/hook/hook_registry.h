#ifndef H344C0C8D_F2FF_4CE5_8B1E_3BA9B1CF7B3C
#define H344C0C8D_F2FF_4CE5_8B1E_3BA9B1CF7B3C

#include <vector>

namespace cctest {

struct Hook;

struct HookRegistry {
  static HookRegistry& before();
  static HookRegistry& after();

  void add(Hook&);
  void exec();

private:
  std::vector<Hook*> hooks;
};

} // namespace cctest

#endif /* H344C0C8D_F2FF_4CE5_8B1E_3BA9B1CF7B3C */
