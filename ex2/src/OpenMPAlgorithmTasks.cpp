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

void OpenMPAlgorithmTasks::run(const std::string& A, const std::string& B, const size_t k){
    const size_t rowLength = A.size();
    const size_t colLength = B.size();

    m_k = k;
    /*
    printf("Row %lu\n", rowLength);
    printf("Col %lu\n", colLength);
    printf("ColxRow %lu\n", colLength*rowLength);
    */
	//std::cout <<  omp_get_max_threads() << "\n";

    std::vector< std::pair<size_t, size_t> > startIndices;

    for(size_t rowBegin=0; rowBegin < rowLength; ++rowBegin) {
        std::pair<size_t, size_t> indexPair(rowBegin, 0);
        startIndices.push_back(indexPair);
    }

    for(size_t colBegin=1; colBegin < colLength; ++colBegin){
        std::pair<size_t, size_t > indexPair(0, colBegin);
        startIndices.push_back(indexPair);
    }


	#pragma omp parallel
	{
		size_t i=0;
		#pragma omp single private(i)
		{
			for(i=0; i<startIndices.size(); ++i)
			#pragma omp task shared(A, B, startIndices)
			{
				//printf("Thread %d starting task for i=%d\n", omp_get_thread_num(), i);
				size_t matchSize = 0;
				size_t row = startIndices.at(i).first;
				size_t col = startIndices.at(i).second;
				for(; col < colLength && row < rowLength; ++col, ++row) {
					if(A[row] == B[col]) {
						++matchSize;
					}
					else if ( matchSize > 0 ) {
						Match match(row-1, col-1, matchSize);
						//printf("%d\n", omp_get_thread_num());
						results[omp_get_thread_num()].push_back(match);
						matchSize = 0;
					}
				}
				//check if last comparison was true (fetch last match)
				if ( matchSize > 0 ) {
						Match match(row-1, col-1, matchSize);
						//printf("%d\n", omp_get_thread_num());
						results[omp_get_thread_num()].push_back(match);
				}
			}
		}
	}
}

Matches OpenMPAlgorithmTasks::collect(){
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
