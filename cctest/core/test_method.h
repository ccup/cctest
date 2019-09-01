#ifndef HBC36D615_D4BB_449A_9829_16E8CE8EC076
#define HBC36D615_D4BB_449A_9829_16E8CE8EC076

namespace cctest {

template <typename Fixture>
struct TestMethod {
private:
  using Method = void(Fixture::*)();

public:
  TestMethod(Method method) : method(method) {
  }

  void run() {
    self.setUp();
    (self.*method)();
    self.tearDown();
  }

private:
  Fixture self;
  Method method;
};

} // namespace cctest

#endif
