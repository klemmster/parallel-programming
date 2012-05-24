#include "OpenMPAlgorithmTasks.h"
#include <omp.h>
#include <stdio.h>
#include <iostream>

OpenMPAlgorithmTasks::OpenMPAlgorithmTasks(const std::string name):
    Testable(name)
{
    int maxThreads = omp_get_max_threads();
    results = std::vector< Matches >(maxThreads);
    for( int i = 0; i < maxThreads; ++i){
        results.at(i).reserve(310000);
    }
}

struct Index{
    size_t r;
    size_t c;
    size_t length;
};

void OpenMPAlgorithmTasks::run(const std::string& A, const std::string& B, const size_t k){
    const size_t rowLength = A.size();
    const size_t colLength = B.size();
    const size_t indexSize = rowLength+colLength-1;

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

	#pragma omp parallel
	{
		size_t i=0;
		#pragma omp single private(i)
		{
			for(i=0; i<indexSize; ++i)
			#pragma omp task shared(A, B, startIndices)
			{
				//printf("Thread %d starting task for i=%d\n", omp_get_thread_num(), i);
				size_t matchSize = 0;
				size_t row = startIndices[i].r;
				size_t col = startIndices[i].c;
				const size_t length = startIndices[i].length;
				for(size_t j = 0; j<length; ++col, ++row, ++j) {
					if(A[row] == B[col]) {
						++matchSize;
					}
					else if ( matchSize > 0 ) {
						if(matchSize >= m_k){
						Match match(row-1, col-1, matchSize);
						//printf("%d\n", omp_get_thread_num());
						results[omp_get_thread_num()].push_back(match);
						}
						matchSize = 0;
					}
				}
				//check if last comparison was true (fetch last match)
				if ( matchSize > 0 ) {
					if(matchSize >= m_k){
						Match match(row-1, col-1, matchSize);
						//printf("%d\n", omp_get_thread_num());
						results[omp_get_thread_num()].push_back(match);
						}
				}
			}
		}
	}

    delete []startIndices;
}

Matches OpenMPAlgorithmTasks::collect(){
    Matches collected;
    std::vector< Matches >::iterator it;
    Matches::iterator it2;
    for(it=results.begin(); it!=results.end(); ++it){
        for(it2=(*it).begin(); it2!=(*it).end(); ++it2){
                collected.push_back((*it2));
        }
    }
    return collected;
}
