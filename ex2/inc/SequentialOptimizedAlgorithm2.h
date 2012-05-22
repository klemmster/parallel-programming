#ifndef SEQUENTIALOPTIMIZEDALGORITHM_H_6FR8SQM
#define SEQUENTIALOPTIMIZEDALGORITHM_H_6FR8SQM

#include <string>
#include <vector>
#include <iostream>
#include "Testable.h"


class SequentialOptimizedAlgorithm2: virtual public Testable
{
public:
    SequentialOptimizedAlgorithm2 (const std::string name);
    virtual ~SequentialOptimizedAlgorithm2 () {};
    virtual void run(const std::string& A, const std::string& B, const size_t k);
    virtual Matches collect();

private:
    std::vector<std::vector< unsigned int > > L;
    size_t rows;
    size_t cols;
    size_t k;
};


#endif /* end of include guard: SEQUENTIALALGORITHM_H_6FR8SQM */

