#ifndef HB19424D1_A5B7_4873_869C_46D64CA62FF0
#define HB19424D1_A5B7_4873_869C_46D64CA62FF0

#include "cctest/base/string_view.h"

namespace cctest {

namespace strutils {

bool to_int32(StringView text, int32_t& value);
bool to_uint32(StringView text, uint32_t& value);

int32_t to_int32(StringView text);
uint32_t to_uint32(StringView text);

std::vector<std::string> split(StringView text, StringView delims);
std::string join(const std::vector<std::string>&, StringView sep);

} // namespace strutils

} // namespace cctest

#endif
