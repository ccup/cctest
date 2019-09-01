file(GLOB_RECURSE cctest_hdrs  
    "*.h"
    "*.hpp"	
)

file(GLOB_RECURSE cctest_tests 
    "*_spec.cc"
    "*_test.cc"	
)

file(GLOB_RECURSE cctest_srcs 
	"*.cc"
)

list(REMOVE_ITEM  cctest_srcs 
	${cctest_tests}
	"${CMAKE_CURRENT_SOURCE_DIR}/main/main.cc"
)

cc_library(
  NAME 
    cctest
  SRCS
    ${cctest_hdrs}
    ${cctest_srcs}
)

add_subdirectory(core)
add_subdirectory(main)
