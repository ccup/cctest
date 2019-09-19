file(GLOB all_tests
    *_test.cc
    *_test.cpp
    *_spec.cc
    *_spec.cpp
)

add_executable(simple_test ${all_tests})
target_link_libraries(simple_test cctest_main cctest)

add_test(NAME simple_test COMMAND simple_test)
