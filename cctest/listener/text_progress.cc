#include "cctest/listener/text_progress.h"
#include "cctest/except/test_failure.h"

namespace cctest {

TextProgress::TextProgress(std::ostream& out)
  : out(out) {}

void TextProgress::startTestRun(const Test&) {
  out << "starting..."
      << std::endl;
}

void TextProgress::startTestCase(const Test&) {
  out << '*';
}

void TextProgress::addFailure(const TestFailure& f) {
  out << (f.isFailure() ? 'F' : 'E');
}

void TextProgress::endTestRun(const Test&) {
  out << std::endl
      << "end."
      << std::endl
      << std::flush;
}

} // namespace cctest
