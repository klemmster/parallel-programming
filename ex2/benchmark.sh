#!/bin/bash

echo "" > benchmark.txt
for i in {1..3}
do
    for THREADS in 1 2 3 4 8
    do
        for k in {1..100..10}
        do
	    for count in {1..3}
	    do
	        echo "dna-A$i dna-B$i; $THREADS; $k;$count;" >> benchmark.txt
		echo "" >> benchmark.txt
		OMP_NUM_THREADS=$THREADS ./ex2 dna-A$i dna-B$i $k >> benchmark.txt
            done
	done
    done
done    

