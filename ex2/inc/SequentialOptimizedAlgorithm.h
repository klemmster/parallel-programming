/* -*  *  *  *  *  *  *  *  *  *  *  *
*   Marcel Karsten -- 343619,
*   Patrick Lorenz -- 341922,
*   Richard Klemm -- 343635
*  *  *  *  *  *  *  *  *  *  *  *  */
#ifndef SEQUENTIALOPTIMIZEDALGORITHM_H_6FR8SQMW
#define SEQUENTIALOPTIMIZEDALGORITHM_H_6FR8SQMW

#include <string>
#include <vector>
#include "Testable.h"

class SequentialOptimizedAlgorithm: virtual public Testable
{
public:
    SequentialOptimizedAlgorithm (const std::string name);
    virtual ~SequentialOptimizedAlgorithm () {};
    virtual void run(const std::string& A, const std::string& B, const size_t k);
    virtual Matches collect();

private:
    std::vector<std::vector< unsigned int > > L;
    size_t rows;
    size_t cols;
    size_t k;
};


#endif /* end of include guard: SEQUENTIALALGORITHM_H_6FR8SQMW */

