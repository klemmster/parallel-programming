#ifndef TESTABLE_H_MIHHYVOB
#define TESTABLE_H_MIHHYVOB

#include <string>

#include "Match.h"

class Testable
{
public:
    Testable () {};
    virtual ~Testable () {};
    virtual void run(const std::string& A, const std::string& B, const size_t k) = 0;
    virtual Matches collect() = 0;

};

#endif /* end of include guard: TESTABLE_H_MIHHYVOB */

