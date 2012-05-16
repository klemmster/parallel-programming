#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdlib.h>

#include "Match.h"

//#include <boost/timer.hpp>

using namespace std;

void computeVariant1(int argc, char const *argv[]) {
    if(argc < 4){
        printf("Not enough arguments\n");
        return;
    }

    string a(argv[1]);
    string b(argv[2]);
    size_t K = atoi(argv[3]);
    size_t N = a.size();
    size_t M = b.size();

    vector<vector< unsigned int > > L;
    L.assign(N, vector< unsigned int > (M));

//    boost::timer seqTimer;

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            if (a[i] == b[j]) {
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

    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < M; ++j){
            if (L[i][j] >= K) {
                if (i+1<N && j+1<M && L[i+1][j+1] > L[i][j])
                    continue;
                printf("%d %d %d\n", i, j, L[i][j]);
            }
        }
    cout << "######################################################" << "\n";
    // for (size_t i = 0; i < N; ++i){
        // for (size_t j = 0; j < M; ++j){
            // cout << " " << L[i][j];
        // }
        // cout << "\n";
    // }

  //  cout << "Elapsed Time: "  << seqTimer.elapsed() << "\n";
}

void computeVariant2(int argc, char const *argv[]) {
	string a(argv[1]);
    string b(argv[2]);
    size_t K = atoi(argv[3]);
    size_t rowLength = a.size();
    size_t colLength = b.size();

	vector< Match > diagonals;
	diagonals.reserve(rowLength + colLength - 1);

	for(size_t rowBegin = 0; rowBegin < rowLength; ++rowBegin) {
		unsigned int matchSize = 0;
		size_t col = 0, row = rowBegin;
		for(; col < colLength && row < rowLength; ++col, ++row) {
			if(a[row] == b[col]) {
				++matchSize;
			}
			else if ( matchSize > 0 ) {
				Match match(row-1, col-1, matchSize);
				diagonals.push_back(match);

				matchSize = 0;
			}
		}
		//check if last comparison was true (fetch last match)
		if ( matchSize > 0 ) {
				Match match(row-1, col-1, matchSize);
				diagonals.push_back(match);
		}
	}

	for(size_t colBegin = 1; colBegin < colLength; ++colBegin) {
		unsigned int matchSize = 0;
		size_t col = colBegin, row = 0;
		for(; col < colLength && row < rowLength; ++col, ++row) {
			if(a[row] == b[col]) {
				++matchSize;
			}
			else if ( matchSize > 0 ) {
				Match match(row-1, col-1, matchSize);
				diagonals.push_back(match);

				matchSize = 0;
			}
		}
		//check if last comparison was true (fetch last match)
		if ( matchSize > 0 ) {
				Match match(row-1, col-1, matchSize);
				diagonals.push_back(match);
		}
	}

	for(size_t i = 0; i < diagonals.size(); ++i) {
		cout << diagonals.at(i) << "\n";
	}
}

int main(int argc, char const *argv[])
{
   computeVariant1(argc, argv);
   cout << "\n\n";
   computeVariant2(argc, argv);
    return 0;
}
