#include "cctest/listener/text/colorful_printer.h"
#include "cctest/base/color.h"
#include "cctest/core/test.h"
#include "cctest/except/test_failure.h"
#include <sstream>

namespace cctest {

struct ColorfulPrinter::Writer {
  Writer(ColorfulPrinter& self) : self(self) {
  }

  void writeOnStartTestRun(const Test& test) const {
    onTestRun(test);
  }

  void writeOnEndTestRun(const Test& test) const {
    onTestRun(test);
    onFinished(test);
  }

  void writeOnStartTestOnce(const Test& test) const {
    onSuiteStarted(test);
  }

  void writeOnEndTestOnce(const Test& test) const {
    onSuiteFinished(test);
  }

  void writeOnStartTestCase(const Test& test) const {
    green(self.out) << "[ RUN      ] ";
    white(self.out) << test.getName() << std::endl;
  }

  void writeOnEndTestCase(const Test& test) const {
    self.lastFailed ? onTestCaseFail() : onTestCaseSucc();
    white(self.out) << test.getName() << caseTime() << std::endl;
  }

  void writeOnAddFailure(const TestFailure& fail) const {
    self.out << fail.getExceptionMsg() << std::endl;
  }

private:
  std::string formatTime(const TimeVal& time) const {
    std::stringstream ss;
    ss << "(" << time.toString() << ")";
    return ss.str();
  }

  std::string caseTime() const {
    return formatTime(self.clock.caseTime());
  }

  std::string suiteTime() const {
    return formatTime(self.clock.suiteTime());
  }

  std::string totalTime() const {
    return formatTime(self.clock.totalTime());
  }

  void onSuite(const Test& test) const {
    green(self.out) << "[----------] ";
    white(self.out) << test.countTestCases()
                    << " tests from "
                    << test.getName();
  }

  void onSuiteStarted(const Test& test) const {
    if (test.getName() != "All Tests") {
      onSuite(test);
      white(self.out) << std::endl;
    }
  }

  void onSuiteFinished(const Test& test) const {
    if (test.getName() != "All Tests") {
      onSuite(test);
      white(self.out) << suiteTime() << std::endl;
    }
  }

  void onTestRun(const Test& test) const {
    green(self.out) << "[==========] ";
    white(self.out) << test.countTestCases()
                    << " test cases."
                    << std::endl;
  }

  void onTestCaseSucc() const {
    green(self.out) << "[       OK ] ";
  }

  void onTestCaseFail() const {
    red(self.out) << "[  FAILED  ] ";
  }

  void onFinished(const Test&) const {
    collectOnFinished();
    listFailures();
  }

  std::ostream& title(std::ostream& os) const {
    return self.status.successful() ? os << green : os << red;
  }

  void collectOnFinished() const {
    title(self.out) << "[  TOTAL   ] ";
    white(self.out) << "PASS: "    << self.collector.passCount()  << "  "
                    << "FAILURE: " << self.collector.failCount()  << "  "
                    << "ERROR: "   << self.collector.errorCount() << "  "
                    << "TIME: "    << totalTime()
                    << std::endl;
  }

  void listFailures() const {
    if (self.status.successful())
      return;

    red(self.out)   << "[  FAILED  ] ";
    white(self.out) << self.collector.failTotal()
                    << " failed tests, listed below:\n";

    self.lister.foreach([&](const TestFailure& failure) {
      red(self.out)   << titleFor(failure);
      white(self.out) << failure.getTestName() << std::endl;
    });
  }

  static const char* titleFor(const TestFailure& err) {
    return err.isFailure() ? "[  FAILURE ] " : "[  ERROR   ] ";
  }

private:
  ColorfulPrinter& self;
};

ColorfulPrinter::ColorfulPrinter(std::ostream& out)
    : lastFailed(false), out(out), writer(new Writer(*this)) {
  addListener(status);
  addListener(collector);
  addListener(lister);
  addListener(clock);
}

ColorfulPrinter::~ColorfulPrinter() {
  delete writer;
}

void ColorfulPrinter::startTestRun(const Test& test) {
  MultiListener::startTestRun(test);
  writer->writeOnStartTestRun(test);
}

void ColorfulPrinter::endTestRun(const Test& test) {
  MultiListener::endTestRun(test);
  writer->writeOnEndTestRun(test);
}

void ColorfulPrinter::startTestCase(const Test& test) {
  lastFailed = false;
  MultiListener::startTestCase(test);
  writer->writeOnStartTestCase(test);
}

void ColorfulPrinter::endTestCase(const Test& test) {
  MultiListener::endTestCase(test);
  writer->writeOnEndTestCase(test);
}

void ColorfulPrinter::startTestOnce(const Test& test) {
  MultiListener::startTestOnce(test);
  writer->writeOnStartTestOnce(test);
}

void ColorfulPrinter::endTestOnce(const Test& test) {
  MultiListener::endTestOnce(test);
  writer->writeOnEndTestOnce(test);
}

void ColorfulPrinter::addFailure(const TestFailure& fail) {
  lastFailed = true;
  MultiListener::addFailure(fail);
  writer->writeOnAddFailure(fail);
}

} // namespace cctest
