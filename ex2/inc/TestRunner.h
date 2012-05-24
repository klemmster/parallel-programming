/* -*  *  *  *  *  *  *  *  *  *  *  *
*   Marcel Karsten -- 343619,
*   Patrick Lorenz -- 341922,
*   Richard Klemm -- 343635
*  *  *  *  *  *  *  *  *  *  *  *  */
#ifndef TESTRUNNER_H_7UAFFJ2O
#define TESTRUNNER_H_7UAFFJ2O

#include <vector>
#include <openssl/sha.h>
#include "Testable.h"

typedef std::vector< Testable* >Testables;

using namespace std;

class TestRunner
{
public:
    TestRunner (Testables testables, const string& A, const string& B, const size_t k, const bool compareResults);
    virtual ~TestRunner () {};

private:

    void getHash(Testable* testable, unsigned char result[]);
    const string A;
    const string B;
    const size_t k;
    SHA_CTX  shaCtx;

};

#endif /* end of include guard: TESTRUNNER_H_7UAFFJ2O */


