#include "TestRunner.h"
#include "Match.h"
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "Stopwatch.h"

TestRunner::TestRunner(Testables testables, const string& A, const string& B,
        const size_t k):
        A(A),
        B(B),
        k(k)
    {

    Testables::iterator it;

    for(it=testables.begin(); it!=testables.end(); ++it){
        Stopwatch stopwatch((*it)->getName(), B.size() * A.size());
        (*it)->run(A, B, k);
        stopwatch.stop();
    }

    /*
    Matches::iterator matchIT;
    for(it = testables.begin(); it!=testables.end(); ++it){
        Matches matches = (*it)->collect();
        for(matchIT = matches.begin(); matchIT!=matches.end(); ++matchIT){
            std::cout << (*matchIT) << "\n";
        }
        std::cout << "DONE " << (*it)->getName() << "\n";
    }
    */

}
