/* -*  *  *  *  *  *  *  *  *  *  *  *
*   Marcel Karsten -- 343619,
*   Patrick Lorenz -- 341922,
*   Richard Klemm -- 343635
*  *  *  *  *  *  *  *  *  *  *  *  */
#ifndef STOPWATCH_H_XU6R2ZE0
#define STOPWATCH_H_XU6R2ZE0
#include <boost/chrono.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>

using namespace boost::chrono;

class Stopwatch
{
public:
    Stopwatch (const std::string id, const long long work):
        start(high_resolution_clock::now()),
        id(id),
        work(work){};
    virtual ~Stopwatch () {
        duration<double> sec = end-start;
        cout.precision(5);
        std::cout << id << " took: " <<
        boost::lexical_cast<string>( duration_cast<milliseconds>(end - start).count())
                  << "ms ("<< work/(sec.count()*1000000) << " MWpS)\n" ;};

    void stop() { end = high_resolution_clock::now(); };

private:
    const time_point<high_resolution_clock> start;
    time_point<high_resolution_clock> end;
    const std::string id;
    const long long work;
};

#endif /* end of include guard: STOPWATCH_H_XU6R2ZE0 */

