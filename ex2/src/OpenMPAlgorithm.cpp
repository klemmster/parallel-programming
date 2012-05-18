#include "OpenMPAlgorithm.h"
#include <omp.h>
#include <stdio.h>

OpenMPAlgorithm::OpenMPAlgorithm(const std::string name):
    Testable(name)
{
    results = std::vector< Matches >(omp_get_max_threads());
}

void OpenMPAlgorithm::run(const std::string& A, const std::string& B, const size_t k){
    const size_t rowLength = A.size();
    const size_t colLength = B.size();

    size_t rowBegin = 0;
    size_t col, row, matchSize;
    #pragma omp parallel for default(none) lastprivate(rowBegin) private( matchSize, col, row) shared(A, B)
	for(rowBegin=0; rowBegin < rowLength; ++rowBegin) {

		matchSize = 0;
		col = 0;
        row = rowBegin;
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

    size_t colBegin = 1;
    #pragma omp parallel for default(none) lastprivate(colBegin) private(matchSize, col, row) shared(A, B)
	for(colBegin = 1; colBegin < colLength; ++colBegin) {

		unsigned int matchSize = 0;
		size_t col = colBegin, row = 0;
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

Matches OpenMPAlgorithm::collect(){
    Matches collected;
    std::vector< Matches >::iterator it;
    for(it=results.begin(); it!=results.end(); ++it){
        collected.insert(collected.end(), (*it).begin(), (*it).end());
    }
    return collected;
}
