#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdlib.h>

#include "TestRunner.h"
#include "SequentialAlgorithm.h"


//#include <boost/timer.hpp>

using namespace std;

void computeVariant2(int argc, char const *argv[]) {
	string a(argv[1]);
    string b(argv[2]);
    size_t rowLength = a.size();
    size_t colLength = b.size();

	Matches diagonals;
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
    if(argc < 4){
        printf("Not enough arguments\n");
        return EXIT_FAILURE;
    }

   string a(argv[1]);
   string b(argv[2]);
   size_t k = atoi(argv[3]);

   SequentialAlgorithm* seq = new SequentialAlgorithm();

   Testables testables;
   testables.push_back(seq);
   TestRunner testRunner(testables, a, b, k);

   delete seq;

   //computeVariant2(argc, argv);
    return 0;
}
