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
};

#endif /* end of include guard: OPENMPALGORITHM_H_W8N1AXO6 */

