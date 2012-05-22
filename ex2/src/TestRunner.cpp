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

    Matches::iterator matchIT;
    Matches lastMatches;
    bool firstRun = true;
    for(it = testables.begin(); it!=testables.end(); ++it){
        Matches matches = (*it)->collect();
        std::sort(matches.begin(), matches.end(), Match::sortFun);
        if(!firstRun){
            if(matches.size() == lastMatches.size()){
                bool isEqual = std::equal(matches.begin(), matches.end(), lastMatches.begin());
                if(!isEqual){
                    for(matchIT = matches.begin(); matchIT!=matches.end(); ++matchIT){
                        std::cout << (*matchIT) << "\n";
                    }
                    std::cout << "##############################################\n";
                    for(matchIT = lastMatches.begin(); matchIT!=lastMatches.end(); ++matchIT){
                        std::cout << (*matchIT) << "\n";
                    }
                    std::cout << "Test FAILed, Not equal\n";
                    return;
                }
            }else{
                std::cout << "Test FAILED, different size\n";
                return;
            }

        }
        lastMatches = matches;
        firstRun = false;
    }
    std::cout << "Success!\n";

}
