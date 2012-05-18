#ifndef SEQUENTIALALGORITHM_H_6FR8SQMW
#define SEQUENTIALALGORITHM_H_6FR8SQMW

#include <string>
#include <vector>
#include "Testable.h"

class SequentialAlgorithm: virtual public Testable
{
public:
    SequentialAlgorithm (const std::string name);
    virtual ~SequentialAlgorithm () {};
    virtual void run(const std::string& A, const std::string& B, const size_t k);
    virtual Matches collect();

private:
    std::vector<std::vector< unsigned int > > L;
    size_t rows;
    size_t cols;
    size_t k;
};


#endif /* end of include guard: SEQUENTIALALGORITHM_H_6FR8SQMW */

