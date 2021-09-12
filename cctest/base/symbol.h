#ifndef H776D37FC_AF32_4575_B054_FD4B353A83C3
#define H776D37FC_AF32_4575_B054_FD4B353A83C3

/////////////////////////////////////////////////////////////////////////
#define __CCTEST_DO_STRING(s) #s
#define CCTEST_STRING(s) __CCTEST_DO_STRING(s)

/////////////////////////////////////////////////////////////////////////
#define __CCTEST_DO_JOIN_AGAIN(s1, s2) s1##s2
#define __CCTEST_DO_JOIN(s1, s2) __CCTEST_DO_JOIN_AGAIN(s1, s2)
#define CCTEST_JOIN(s1, s2) __CCTEST_DO_JOIN(s1, s2)

/////////////////////////////////////////////////////////////////////////
#ifdef __COUNTER__
# define CCTEST_UNIQUE_ID __COUNTER__
#else
# define CCTEST_UNIQUE_ID __LINE__
#endif

/////////////////////////////////////////////////////////////////////////
#define CCTEST_UNIQUE_NAME(prefix) CCTEST_JOIN(prefix, CCTEST_UNIQUE_ID)

#endif
