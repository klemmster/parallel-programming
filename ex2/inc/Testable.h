/* -*  *  *  *  *  *  *  *  *  *  *  *
*   Marcel Karsten -- 343619,
*   Patrick Lorenz -- 341922,
*   Richard Klemm -- 343635
*  *  *  *  *  *  *  *  *  *  *  *  */
#ifndef TESTABLE_H_MIHHYVOB
#define TESTABLE_H_MIHHYVOB

#include <string>

#include "Match.h"

class Testable
{
public:
    Testable (const std::string name):
        m_name(name){};
    virtual ~Testable () {};
    virtual void run(const std::string& A, const std::string& B, const size_t k) = 0;
    virtual Matches collect() = 0;

    const std::string& getName() const { return m_name; };

protected:

    const std::string m_name;

};

#endif /* end of include guard: TESTABLE_H_MIHHYVOB */

