cc_test(
  NAME
    test_collector_spec
  SRCS
    "test_collector_spec.cc"
  DEPS
    cctest
    cctest_main
)

cc_test(
  NAME
    failure_list_spec
  SRCS
    failure_list_spec.cc
  DEPS
    cctest
    cctest_main
)

cc_test(
  NAME
    test_status_spec
  SRCS
    "test_status_spec.cc"
  DEPS
    cctest::cctest
)

cc_test(
  NAME
    text_progress_spec
  SRCS
    "text_progress_spec.cc"
  DEPS
    cctest::cctest
)

cc_test(
  NAME
    time_collector_spec
  SRCS
    "time_collector_spec.cc"
  DEPS
    cctest::cctest
)
