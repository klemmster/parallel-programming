#include "TestRunner.h"
#include "Match.h"
#include <iostream>

TestRunner::TestRunner(Testables testables, const string& A, const string& B,
        const size_t k):
        A(A),
        B(B),
        k(k)
    {

    Testables::iterator it;

    for(it=testables.begin(); it!=testables.end(); ++it){
        //TODO: Measure Runtime
        (*it)->run(A, B, k);
    }

    std::vector< Matches >resultSet;
    resultSet.reserve(testables.size());
    for(it = testables.begin(); it!=testables.end(); ++it){
        resultSet.push_back((*it)->collect());
    }

    std::vector< Matches >::iterator resultIT;
    Matches::iterator matchIT;
    for(resultIT = resultSet.begin(); resultIT!=resultSet.end(); ++resultIT){
        for(matchIT = (*resultIT).begin(); matchIT!=(*resultIT).end(); ++matchIT){
            std::cout << (*matchIT) << "\n";
        }
        std::cout << "DONE SET \n\n";
    }
}
