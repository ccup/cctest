file(GLOB_RECURSE cctest_hdrs  
  "*.h"
  "*.hpp"	
)

file(GLOB_RECURSE cctest_main_src 
  "main.cc"
)

file(GLOB_RECURSE cctest_srcs 
  "*.cc"
)

list(REMOVE_ITEM cctest_srcs ${cctest_main_src})

cc_library(
  NAME 
    cctest
  HDRS 
    ${cctest_hdrs}
  SRCS
    ${cctest_srcs}
)

cc_library(
  NAME 
    cctest_main
  SRCS
    ${cctest_main_src}
  DEPS
    cctest
)

add_library(cctest::main ALIAS cctest_main)
