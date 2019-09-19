file(GLOB all_tests
    *_test.cc
    *_test.cpp
    *_spec.cc
    *_spec.cpp
)

add_executable(stlspec_test ${all_tests})
target_link_libraries(stlspec_test cctest_main cctest)

add_test(NAME stlspec_test COMMAND stlspec_test)
