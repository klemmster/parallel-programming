#!/bin/bash
###########################
#  Marcel Karsten -- 343619,
#  Patrick Lorenz -- 341922,
#  Richard Klemm -- 343635
###########################
echo "" > benchmark.txt
for i in {1..3}
do
    for THREADS in 1 2 3 4 8
    do
        for k in {1..1001..200}
        do
	    for count in {1..3}
	    do
	        echo "$THREADS, $k, $count"
		echo -n "dna-A1; dna-B1; $THREADS; $k;$count" >> benchmark.txt
		OMP_NUM_THREADS=$THREADS ./ex2 dna-A$i dna-B$i $k true >> benchmark.txt
		echo "" >> benchmark.txt
            done
	done
    done
done

