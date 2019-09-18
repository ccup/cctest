#ifndef HC4F46FB4_5084_4646_BEDB_39CF5E71DA39
#define HC4F46FB4_5084_4646_BEDB_39CF5E71DA39

#include <ostream>

namespace cctest {

#define DECL_COLOR(color) \
std::ostream& color(std::ostream&);

DECL_COLOR(white)
DECL_COLOR(red)
DECL_COLOR(green)
DECL_COLOR(yellow)
DECL_COLOR(blue)
DECL_COLOR(magenta)
DECL_COLOR(cyan)

} // namespace cctest

#endif
