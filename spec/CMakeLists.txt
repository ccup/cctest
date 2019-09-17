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

cc_test(
  NAME
    test_fixture_spec
  SRCS
    "test_fixture_spec.cc"
  DEPS
    cctest::cctest
)

cc_test(
  NAME
    test_suite_spec
  SRCS
    "test_suite_spec.cc"
  DEPS
    cctest::cctest
)

cc_test(
  NAME
    test_result_spec
  SRCS
    "test_result_spec.cc"
  DEPS
    cctest::cctest
)

cc_test(
  NAME
    test_collector_spec
  SRCS
    "test_collector_spec.cc"
  DEPS
    cctest::cctest
)

cc_test(
  NAME
    failure_list_spec
  SRCS
    "failure_list_spec.cc"
  DEPS
    cctest::cctest
)
