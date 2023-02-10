#include <iostream>
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include "solve/solve.h"

#include <cmath>

class Test : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(Test);
  CPPUNIT_TEST(testOneRoot);
  CPPUNIT_TEST(testOneRootDiscriminantLessThanEps);
  CPPUNIT_TEST(testNoRoots);
  CPPUNIT_TEST(testTwoRoots);
  CPPUNIT_TEST(testCoeffAIsZero);
  CPPUNIT_TEST(testNonNumericValues);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp(void) {
    solve_obj = new CSolve();
  }
  void tearDown(void) {
    delete solve_obj;
  }

private:
    CSolve *solve_obj;

protected:

  void testOneRoot(void) {

    double a = 1.0;
    double b = 2.0;
    double c = 1.0;
    double eps = 0.00000001;
    std::vector<double> arrange_vec{-1};

    CPPUNIT_ASSERT(arrange_vec == solve_obj->solve(a, b, c, eps));
  }

  void testNoRoots()
{
    double a = 1;
    double b = 0;
    double c = 1;
    double eps = 0.00000001;
    std::vector<double> arrange_vec = {};

    CPPUNIT_ASSERT(solve_obj->solve(a, b, c, eps) == arrange_vec);
}

void testTwoRoots()
{
    double a = 1;
    double b = 0;
    double c = -1;
    double eps = 0.00000001;
    std::vector<double> arrange_vec = {1, -1};

    CPPUNIT_ASSERT(solve_obj->solve(a, b, c, eps) == arrange_vec);
}

void testOneRootDiscriminantLessThanEps()
{
    double a =   0.000000001;
    double b =   0.00001;
    double c =   0;
    double eps = 0.00000001;
    std::vector<double> arrange_vec = {-5000};

    CPPUNIT_ASSERT(solve_obj->solve(a, b, c, eps) == arrange_vec);
}

void testCoeffAIsZero()
{
    double eps = 0.00000001;
    double a = 0.00000001;
    double b = 2;
    double c = 1;
    std::vector<double> arrange_vec = {};
    string err = "\'a\' не может быть равно " +  std::to_string(eps);

    CPPUNIT_ASSERT_THROW_MESSAGE("ERRRORRRR", solve_obj->solve(a, b, c, eps), coeff_a_is_zero_error);
}

void testNonNumericValues()
{
    double n = std::nan("1");
    double inf = INFINITY;

    double a = n;
    double b = 2;
    double c = 1;
    double eps = 0.00000001;
    std::vector<double> arrange_vec = {};

    CPPUNIT_ASSERT_THROW(solve_obj->solve(a, b, c, eps), coeff_is_non_numeric_error);

    a = 1;
    b = inf;
    c = 1;
    eps = 0.00000001;
    arrange_vec = {};

    CPPUNIT_ASSERT_THROW(solve_obj->solve(a, b, c, eps), coeff_is_non_numeric_error);
}
};


CPPUNIT_TEST_SUITE_REGISTRATION(Test);

int main()

{
  CPPUNIT_NS::TestResult controller;

  CPPUNIT_NS::TestResultCollector result;
  controller.addListener(&result);

  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener(&progress);

  CPPUNIT_NS::TestRunner runner;
  runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
  runner.run(controller);

  return result.wasSuccessful() ? 0 : 1;
}
