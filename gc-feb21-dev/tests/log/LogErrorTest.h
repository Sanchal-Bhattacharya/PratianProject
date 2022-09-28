#include <iostream>
#include <string>
#include <list>
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
#include <netinet/in.h>

#include "Log.h"
# include <string>

using namespace CppUnit;
using namespace std;
using namespace gc::util;
//-----------------------------------------------------------------------------

class TestLogError : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestLogError);
    	CPPUNIT_TEST(testError1);
    	CPPUNIT_TEST(testError2);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    void tearDown(void);

protected:
    void testError1(void);
    void testError2(void);
	LogManager * logManager;
	LogData * logData;
};
