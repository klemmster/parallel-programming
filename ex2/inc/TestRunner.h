#ifndef TESTRUNNER_H_7UAFFJ2O
#define TESTRUNNER_H_7UAFFJ2O

#include <vector>
#include "Testable.h"

typedef std::vector< Testable* >Testables;

using namespace std;

class TestRunner
{
public:
    TestRunner (Testables testables, const string& A, const string& B, const size_t k);
    virtual ~TestRunner () {};

private:
    const string A;
    const string B;
    const size_t k;
    /* data */
};

#endif /* end of include guard: TESTRUNNER_H_7UAFFJ2O */


