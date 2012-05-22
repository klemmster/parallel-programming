#ifndef OPENMPALGORITHTASKSM_H_W8N1AXO6
#define OPENMPALGORITHTASKSM_H_W8N1AXO6

#include <string>
#include <vector>
#include "Testable.h"

class OpenMPAlgorithmTasks: virtual public Testable
{
public:
    OpenMPAlgorithmTasks (const std::string name);
    virtual ~OpenMPAlgorithmTasks () {};
    virtual void run(const std::string& A, const std::string& B, const size_t k);
    virtual Matches collect();

private:
    std::vector< Matches > results;
};

#endif /* end of include guard: OPENMPALGORITHTASKSM_H_W8N1AXO6 */

