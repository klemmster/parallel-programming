#include <stdio.h>
#include <stdlib.h>

#include "TestRunner.h"
#include "SequentialAlgorithm.h"
#include "OpenMPAlgorithm.h"

//#include <boost/timer.hpp>

using namespace std;

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
   OpenMPAlgorithm* omp = new OpenMPAlgorithm();

   Testables testables;
   testables.push_back(seq);
   testables.push_back(omp);

   TestRunner testRunner(testables, a, b, k);

   delete seq;
   delete omp;

   return EXIT_SUCCESS;
}
