/* -*  *  *  *  *  *  *  *  *  *  *  *
*   Marcel Karsten -- 343619,
*   Patrick Lorenz -- 341922,
*   Richard Klemm -- 343635
*  *  *  *  *  *  *  *  *  *  *  *  */
#include "SequentialOptimizedAlgorithm.h"
#include <iostream>

SequentialOptimizedAlgorithm::SequentialOptimizedAlgorithm(const std::string name):
    Testable(name){

}

void SequentialOptimizedAlgorithm::run(const std::string& A, const std::string& B, const size_t k){
    rows = A.size();
    cols = B.size();
    this->k = k;
    L.assign(rows, std::vector< unsigned int > (cols));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (A[i] == B[j]) {
                if (i == 0 || j == 0){
                    L[i][j] = 1;
                }else{
                    L[i][j] = L[i-1][j-1] + 1;
                }
            } else {
                L[i][j] = 0;
            }
        }
    }
}

Matches SequentialOptimizedAlgorithm::collect(){
    Matches matches;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j){
			if (L[i][j] >= k) {
                if (i+1<rows && j+1<cols && L[i+1][j+1] > L[i][j])
                    continue;
                matches.push_back(Match(i,j, L[i][j]));
            }
        }
	}

    return matches;
}
