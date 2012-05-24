#include "OpenMPAlgorithm.h"
#include <omp.h>
#include <stdio.h>

OpenMPAlgorithm::OpenMPAlgorithm(const std::string name):
    Testable(name)
{
    int maxThreads = omp_get_max_threads();
    results = std::vector< Matches >(maxThreads);
}

struct Index{
    size_t r;
    size_t c;
    size_t length;
};

void OpenMPAlgorithm::run(const std::string& A, const std::string& B, const size_t k){
    const size_t rowLength = A.size();
    const size_t colLength = B.size();
    const size_t indexSize = rowLength+colLength-1;
    /*
    printf("Row %lu\n", rowLength);
    printf("Col %lu\n", colLength);
    printf("ColxRow %lu\n", colLength*rowLength);
    */


    m_k = k;
    Index* startIndices = new Index[indexSize];
    size_t minSize = colLength < rowLength ? colLength : rowLength;

    size_t i = 0;
    for(size_t rowBegin=0; rowBegin < rowLength; ++rowBegin) {
	Index index;
	index.r = rowBegin;
	index.c = 0;
	if(rowBegin + minSize < rowLength){
	    index.length = minSize;
	}else{
	    index.length = rowLength - rowBegin;
	}
        startIndices[i++] = index;
    }

    for(size_t colBegin=1; colBegin < colLength; ++colBegin){
	Index index;
	index.r = 0;
	index.c = colBegin;
        if(colBegin + minSize < colLength){
	    index.length = minSize;
	}else{
	    index.length = colLength - colBegin;
	}
	startIndices[i++] = index;
    }

    #pragma omp parallel for
    for(size_t i=0; i<indexSize; ++i)
    //#pragma omp task for default(none) shared(A, B)
    {
        size_t matchSize = 0;
        size_t row = startIndices[i].r;
        size_t col = startIndices[i].c;
	const size_t length = startIndices[i].length;
        for(size_t j = 0; j<length; ++col, ++row, ++j) {
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

    delete[] startIndices;
}

Matches OpenMPAlgorithm::collect(){
    Matches collected;
    std::vector< Matches >::iterator it;
    Matches::iterator it2;
    for(it=results.begin(); it!=results.end(); ++it){
        for(it2=(*it).begin(); it2!=(*it).end(); ++it2){
            if((*it2).getK() >= m_k){
                collected.push_back((*it2));
            }
        }
    }
    return collected;
}

