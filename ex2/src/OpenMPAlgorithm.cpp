#include "OpenMPAlgorithm.h"

void OpenMPAlgorithm::run(const std::string& A, const std::string& B, const size_t k){
    size_t rowLength = A.size();
    size_t colLength = B.size();

	matches.reserve(rowLength + colLength - 1);

	for(size_t rowBegin = 0; rowBegin < rowLength; ++rowBegin) {
		unsigned int matchSize = 0;
		size_t col = 0, row = rowBegin;
		for(; col < colLength && row < rowLength; ++col, ++row) {
			if(A[row] == B[col]) {
				++matchSize;
			}
			else if ( matchSize > 0 ) {
				Match match(row-1, col-1, matchSize);
				matches.push_back(match);

				matchSize = 0;
			}
		}
		//check if last comparison was true (fetch last match)
		if ( matchSize > 0 ) {
				Match match(row-1, col-1, matchSize);
				matches.push_back(match);
		}
	}

	for(size_t colBegin = 1; colBegin < colLength; ++colBegin) {
		unsigned int matchSize = 0;
		size_t col = colBegin, row = 0;
		for(; col < colLength && row < rowLength; ++col, ++row) {
			if(A[row] == B[col]) {
				++matchSize;
			}
			else if ( matchSize > 0 ) {
				Match match(row-1, col-1, matchSize);
				matches.push_back(match);

				matchSize = 0;
			}
		}
		//check if last comparison was true (fetch last match)
		if ( matchSize > 0 ) {
				Match match(row-1, col-1, matchSize);
				matches.push_back(match);
		}
	}
}

Matches OpenMPAlgorithm::collect(){
    return matches;
}
