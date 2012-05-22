#include "SequentialOptimizedAlgorithm2.h"

SequentialOptimizedAlgorithm2::SequentialOptimizedAlgorithm2(const std::string name):
    Testable(name){

}

void SequentialOptimizedAlgorithm2::run(const std::string& A, const std::string& B, const size_t k){
    rows = A.size();
    cols = B.size();
    this->k = k;
    L.assign(rows, std::vector< unsigned int > (cols));

    size_t i,j,it,jt;
    size_t temp_rows = rows-5;

    for (i=0; i < temp_rows; i+=5) {

       for (j = 0; j < cols; ++j){
            jt = j-1;
            if (A[i] == B[j]) L[i][j] = (i == 0 || j == 0) ? 1 : L[i-1][jt] + 1;
            else              L[i][j] = 0;

            it = i+1;

            if (A[it] == B[j]) L[it][j] = (j == 0) ? 1 : L[it-1][jt] + 1;
            else              L[it][j] = 0;

            it++;


            if (A[it] == B[j]) L[it][j] = (j == 0) ? 1 : L[it-1][jt] + 1;
            else              L[it][j] = 0;

            it++;

            if (A[it] == B[j]) L[it][j] = ( j == 0) ? 1 : L[it-1][jt] + 1;
            else              L[it][j] = 0;

            it++;
            if (A[it] == B[j]) L[it][j] = ( j == 0) ? 1 : L[it-1][jt] + 1;
            else              L[it][j] = 0;
        }
    }
    if( i > 4){
        i-= 4;
    }
    for (; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            if (A[i] == B[j]) {
                L[i][j] = (i == 0 || j == 0) ? 1 : L[i-1][j-1] + 1;
            } else {
                L[i][j] = 0;
            }
        }
    }
}

Matches SequentialOptimizedAlgorithm2::collect(){
    Matches matches;
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j){
            if (L[i][j] >= k) {
                if (i+1<rows && j+1<cols && L[i+1][j+1] > L[i][j])
                    continue;
                matches.push_back(Match(i,j, L[i][j]));
            }
        }
    return matches;
}
