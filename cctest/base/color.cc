#include "cctest/base/color.h"

namespace cctest {

#define __white__   "\033[0m"
#define __red__     "\033[1;31m"
#define __green__   "\033[1;32m"
#define __yellow__  "\033[1;33m"
#define __blue__    "\033[1;34m"
#define __magenta__ "\033[1;35m"
#define __cyan__    "\033[1;36m"

#define DEF_COLOR(color)                \
std::ostream& color(std::ostream& os) { \
    return os << __##color##__;         \
}

DEF_COLOR(white)
DEF_COLOR(red)
DEF_COLOR(green)
DEF_COLOR(yellow)
DEF_COLOR(blue)
DEF_COLOR(magenta)
DEF_COLOR(cyan)

} // namespace cctest
