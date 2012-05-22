#include <stdio.h>
#include <stdlib.h>

#include "File.h"
#include "TestRunner.h"
#include "SequentialAlgorithm.h"
#include "SequentialOptimizedAlgorithm.h"
#include "SequentialOptimizedAlgorithm2.h"
#include "OpenMPAlgorithm.h"
#include "OpenMPAlgorithmTasks.h"

using namespace std;

int main(int argc, char const *argv[])
{
    if(argc < 4){
        printf("Not enough arguments\n");
        printf("SampleCall: ./ex2 file1 file2 NUMRESULTS\n");
        printf("\n -- Note: file is expected to be in data\n");
        return EXIT_FAILURE;
    }

   string a(argv[1]);
   string b(argv[2]);
   size_t k = atoi(argv[3]);

   File fa(a);
   File fb(b);

   SequentialAlgorithm* seq = new SequentialAlgorithm("Sequential");
   OpenMPAlgorithm* omp = new OpenMPAlgorithm("OpenMP");
   OpenMPAlgorithmTasks* ompTasks = new OpenMPAlgorithmTasks("OpenMP-Tasks");
   SequentialOptimizedAlgorithm* seqOpt = new SequentialOptimizedAlgorithm("Optimized Sequential");
   SequentialOptimizedAlgorithm2* seqOpt2 = new SequentialOptimizedAlgorithm2("Optimized Sequential part two");

   Testables testables;
   testables.push_back(seq);
   testables.push_back(omp);
   testables.push_back(ompTasks);
   testables.push_back(seqOpt);
   testables.push_back(seqOpt2);

   TestRunner testRunner(testables, fa.getContent(), fb.getContent(), k);

   delete seq;
   delete omp;
   delete seqOpt;

   return EXIT_SUCCESS;
}
