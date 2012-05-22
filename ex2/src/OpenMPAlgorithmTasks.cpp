#include "OpenMPAlgorithmTasks.h"
#include <omp.h>
#include <stdio.h>

OpenMPAlgorithmTasks::OpenMPAlgorithmTasks(const std::string name):
    Testable(name)
{
    results = std::vector< Matches >(omp_get_max_threads());
    results.at(0).reserve(310000);
    results.at(1).reserve(310000);
    results.at(2).reserve(310000);
    results.at(3).reserve(310000);
}

void OpenMPAlgorithmTasks::run(const std::string& A, const std::string& B, const size_t k){
    const size_t rowLength = A.size();
    const size_t colLength = B.size();

    /*
    printf("Row %lu\n", rowLength);
    printf("Col %lu\n", colLength);
    printf("ColxRow %lu\n", colLength*rowLength);
    */


    std::vector< std::pair<size_t, size_t> > startIndices;

    for(size_t rowBegin=0; rowBegin < rowLength; ++rowBegin) {
        std::pair<size_t, size_t> indexPair(rowBegin, 0);
        startIndices.push_back(indexPair);
    }

    for(size_t colBegin=1; colBegin < colLength; ++colBegin){
        std::pair<size_t, size_t > indexPair(0, colBegin);
        startIndices.push_back(indexPair);
    }

    #pragma omp parallel for
    for(size_t i=0; i<startIndices.size(); ++i)
    //#pragma omp task for default(none) shared(A, B)
    {
        size_t matchSize = 0;
        size_t row = startIndices.at(i).first;
        size_t col = startIndices.at(i).second;
        for(; col < colLength && row < rowLength; ++col, ++row) {
            if(A[row] == B[col]) {
                ++matchSize;
            }
            else if ( matchSize > 0 ) {
                Match match(row-1, col-1, matchSize);
                results[omp_get_thread_num()].push_back(match);
                matchSize = 0;
            }
        }
        //check if last comparison was true (fetch last match)
        if ( matchSize > 0 ) {
                Match match(row-1, col-1, matchSize);
                results[omp_get_thread_num()].push_back(match);
        }
    }
}

Matches OpenMPAlgorithmTasks::collect(){
    Matches collected;
    std::vector< Matches >::iterator it;
    for(it=results.begin(); it!=results.end(); ++it){
        collected.insert(collected.end(), (*it).begin(), (*it).end());
    }
    return collected;
}
