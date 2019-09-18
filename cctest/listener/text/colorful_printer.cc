#include "cctest/listener/text/colorful_printer.h"
#include "cctest/base/color.h"
#include "cctest/core/test.h"
#include "cctest/except/test_failure.h"

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

  void writeOnStartTestSuite(const Test& test) const {
    onSuiteStarted(test);
  }

  void writeOnEndTestSuite(const Test& test) const {
    onSuiteFinished(test);
  }

  void writeOnStartTestCase(const Test& test) const {
    green(self.out) << "[ RUN      ] ";
    white(self.out) << test.getName() << std::endl;
  }

  void writeOnEndTestCase(const Test& test) const {
    self.lastFailed ? onTestCaseFail() : onTestCaseSucc();
    white(self.out) << test.getName()
                    << "(" << self.clock.caseTime().toString() << ")"
                    << std::endl;
  }

  void writeOnAddFailure(const TestFailure& fail) const {
    self.out << fail.getExceptionMsg() << std::endl;
  }

private:
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
      white(self.out) << "(" << self.clock.suiteTime().toString() << " total)"
                      << std::endl << std::endl;
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

  std::ostream& title(std::ostream& out) const {
    return self.status.successful() ? out << green : out << red;
  }

  void collectOnFinished() const {
    title(self.out) << "[  TOTAL   ] ";
    white(self.out) << "PASS: "    << self.collector.passCount()  << "  "
                    << "FAILURE: " << self.collector.failCount()  << "  "
                    << "ERROR: "   << self.collector.errorCount() << "  "
                    << "TIME: "    << self.clock.totalTime().toString()
                    << std::endl;
  }

  void listFailures() const {
    if (self.status.successful())
      return;

    red(self.out)   << "[  FAILED  ] ";
    white(self.out) << self.collector.failTotal()
                    << " tests, listed below:\n";

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
}

ColorfulPrinter::~ColorfulPrinter() {
  delete writer;
}

void ColorfulPrinter::startTestRun(const Test& test) {
  clock.startTestRun(test);
  writer->writeOnStartTestRun(test);
}

void ColorfulPrinter::endTestRun(const Test& test) {
  writer->writeOnEndTestRun(test);
}

void ColorfulPrinter::startTestCase(const Test& test) {
  lastFailed = false;
  collector.startTestCase(test);
  clock.startTestCase(test);

  writer->writeOnStartTestCase(test);
}

void ColorfulPrinter::endTestCase(const Test& test) {
  collector.endTestCase(test);
  clock.endTestCase(test);

  writer->writeOnEndTestCase(test);
}

void ColorfulPrinter::startTestSuite(const Test& test) {
  writer->writeOnStartTestSuite(test);
}

void ColorfulPrinter::endTestSuite(const Test& test) {
  writer->writeOnEndTestSuite(test);
}

void ColorfulPrinter::addFailure(const TestFailure& fail) {
  lastFailed = true;
  status.addFailure(fail);
  collector.addFailure(fail);
  lister.addFailure(fail);

  writer->writeOnAddFailure(fail);
}

} // namespace cctest
