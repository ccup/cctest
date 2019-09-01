cc_test(
  NAME
    test_method_spec
  SRCS
    "test_method_spec.cc"
  DEPS
    cctest::cctest
)

cc_test(
  NAME
    test_case_spec
  SRCS
    "test_case_spec.cc"
  DEPS
    cctest::cctest
)
