/* -*  *  *  *  *  *  *  *  *  *  *  *
*   Marcel Karsten -- 343619,
*   Patrick Lorenz -- 341922,
*   Richard Klemm -- 343635
*  *  *  *  *  *  *  *  *  *  *  *  */
#ifndef OPENMPALGORITHM_H_W8N1AXO6
#define OPENMPALGORITHM_H_W8N1AXO6

#include <string>
#include <vector>
#include "Testable.h"

class OpenMPAlgorithm: virtual public Testable
{
public:
    OpenMPAlgorithm (const std::string name);
    virtual ~OpenMPAlgorithm () {};
    virtual void run(const std::string& A, const std::string& B, const size_t k);
    virtual Matches collect();

private:
    std::vector< Matches > results;
    size_t m_k;
};

#endif /* end of include guard: OPENMPALGORITHM_H_W8N1AXO6 */

