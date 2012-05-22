#include "SequentialOptimizedAlgorithm2.h"

SequentialOptimizedAlgorithm2::SequentialOptimizedAlgorithm2(const std::string name):
    Testable(name){

}

void SequentialOptimizedAlgorithm2::run(const std::string& A, const std::string& B, const size_t k){
    rows = A.size();
    cols = B.size();
    this->k = k;
    L.assign(rows, std::vector< unsigned int > (cols));

    size_t i = 0,j,it,jt;

    if( rows > 4){
        size_t temp_rows = rows-5;

        L[0][0] = (A[0] == B[0]) ? 1 : 0;
        L[1][0] = (A[1] == B[0]) ? 1 : 0;
        L[2][0] = (A[2] == B[0]) ? 1 : 0;
        L[3][0] = (A[3] == B[0]) ? 1 : 0;
        L[4][0] = (A[4] == B[0]) ? 1 : 0;

        for (j = 1; j < cols; ++j){
             jt = j-1;

             L[0][j] = (A[0] == B[j]) ? 1 : 0;
             L[1][j] = (A[1] == B[j]) ? L[0][jt] + 1 : 0;
             L[2][j] = (A[2] == B[j]) ? L[1][jt] + 1 : 0;
             L[3][j] = (A[3] == B[j]) ? L[2][jt] + 1 : 0;
             L[4][j] = (A[4] == B[j]) ? L[3][jt] + 1 : 0;
         }

        for (i=5; i < temp_rows; i+=5) {

            j=0;
            it = i+1;
            L[i][j] = (A[i] == B[j]) ? 1 : 0;
            L[it][j] = (A[it] == B[j]) ? 1 : 0;
            L[++it][j] = (A[it] == B[j]) ? 1 : 0;
            L[++it][j] = (A[it] == B[j]) ? 1 : 0;
            L[++it][j] = (A[it] == B[j]) ? 1 : 0;

           for (j = 1; j < cols; ++j){
                jt = j-1;
                it = i+1;
                L[i][j] = (A[i] == B[j]) ? L[i-1][jt] + 1 : 0;
                L[it][j] = (A[it] == B[j]) ? L[it-1][jt] + 1 : 0;
                L[++it][j] = (A[it] == B[j]) ? L[it-1][jt] + 1 : 0;
                L[++it][j] = (A[it] == B[j]) ? L[it-1][jt] + 1 : 0;
                L[++it][j] = (A[it] == B[j]) ? L[it-1][jt] + 1 : 0;
            }
        }

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
