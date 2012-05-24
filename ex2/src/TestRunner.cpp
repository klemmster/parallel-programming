/* -*  *  *  *  *  *  *  *  *  *  *  *
*   Marcel Karsten -- 343619,
*   Patrick Lorenz -- 341922,
*   Richard Klemm -- 343635
*  *  *  *  *  *  *  *  *  *  *  *  */
#include "TestRunner.h"
#include "Match.h"
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <cstring>
#include <new>
#include <boost/lexical_cast.hpp>
//#include "Stopwatch.h"
#include "StopwatchNoBoost.h"

TestRunner::TestRunner(Testables testables, const string& A, const string& B,
        const size_t k, const bool compareResults):
        A(A),
        B(B),
        k(k)
    {

    Testables::iterator it;

    unsigned char currentHash[SHA_DIGEST_LENGTH];
    unsigned char lastHash[SHA_DIGEST_LENGTH];
    bool firstRun = true;
    bool failed = false;

    for(it=testables.begin(); it!=testables.end(); ++it){
	try{
        StopwatchNoBoost stopwatch((*it)->getName(), B.size() * A.size());
        (*it)->run(A, B, k);
        stopwatch.stop();

        if( compareResults ){
            getHash((*it), currentHash);
            if(firstRun == false){
                if( 0 != memcmp(&currentHash[0], &lastHash[0], SHA_DIGEST_LENGTH)){
                std::cerr << "FAILED\n";
                failed = true;
                }
            }

            std::copy(&currentHash[0], &currentHash[SHA_DIGEST_LENGTH], &lastHash[0]);
            firstRun = false;
        }

	}catch(std::bad_alloc& e){
	    cerr << (*it)->getName() << " failed. Reason: " << e.what() << "\n";
    }
	delete (*it);
    }
    if(compareResults){
       if(!failed){
        std::cout << "Success!\n";
        }else{
        std::cerr << "SOME TESTS FAILED!\n";
        }
    }
}

void TestRunner::getHash(Testable* testable, unsigned char result[]){
    Matches matches = testable->collect();
    std::sort(matches.begin(), matches.end(), Match::sortFun);

    Matches::iterator it;

    SHA1_Init(&shaCtx);
    for(it=matches.begin(); it!=matches.end(); ++it){
    	std::string matchStr = (*it).toString();
        SHA1_Update(&shaCtx, matchStr.c_str(), matchStr.size());
    }
    SHA1_Final(result, &shaCtx);
}
