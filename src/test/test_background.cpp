#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <fakeit.hpp>
#include "background.h"

using namespace fakeit;

class BackgroundTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(BackgroundTest);
  CPPUNIT_TEST(runTestFalse);
  CPPUNIT_TEST(runTestTrue);
  CPPUNIT_TEST_SUITE_END();

public:
  BackgroundTest() : CppUnit::TestCase()
  {
  }

  void runTestFalse()
  {
    CPPUNIT_ASSERT( false );
  }

  void runTestTrue()
  {
    CPPUNIT_ASSERT( true );
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION( BackgroundTest );

int main(int argc, char* argv[])
{
  CPPUNIT_NS::TestResult test_result;

  CPPUNIT_NS::TestResultCollector collectedresults;
  test_result.addListener(&collectedresults);

  CPPUNIT_NS::BriefTestProgressListener progress;
  test_result.addListener(&progress);

  CPPUNIT_NS::TestRunner test_runner;
  test_runner.addTest(
    CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
  test_runner.run(test_result);

  CPPUNIT_NS::CompilerOutputter compilerOutputter(&collectedresults,
                                                  std::cerr);
  compilerOutputter.write();

  return collectedresults.wasSuccessful() ? 0 : 1;
}
