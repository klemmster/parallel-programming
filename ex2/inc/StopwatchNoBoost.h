/* -*  *  *  *  *  *  *  *  *  *  *  *
*   Marcel Karsten -- 343619,
*   Patrick Lorenz -- 341922,
*   Richard Klemm -- 343635
*  *  *  *  *  *  *  *  *  *  *  *  */
#ifndef STOPWATCHNOBOOST_H
#define STOPWATCHNOBOOST_H

#include <sys/time.h>
#include <iostream>

class StopwatchNoBoost
{
public:
    StopwatchNoBoost (const std::string id, const long long work):
        start(),
        id(id),
        work(work){
			gettimeofday(&start, 0);
		};
    virtual ~StopwatchNoBoost () {
   	float seconds =(end.tv_sec - start.tv_sec);
        float millis = (seconds*1000) + ((end.tv_usec-start.tv_usec)/1000.0);
        cout.precision(5);
        //std::cout << id << " took: " << millis
        //          << "ms ("<< work/(millis*1000.0) << " MWpS)\n" ;};

        std::cout <<";"<< millis << ";" << work/(millis*1000.0) ;};
    void stop() { gettimeofday(&end, 0); };

private:
    timeval start;
    timeval end;
    const std::string id;
    const long long work;
};

#endif /* end of include guard: STOPWATCHNOBOOST_H */

