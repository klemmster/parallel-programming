#!/bin/bash
###########################
#  Marcel Karsten -- 343619,
#  Patrick Lorenz -- 341922,
#  Richard Klemm -- 343635
###########################
echo "Bash version ${BASH_VERSION}..."
echo "file1; file2; threads; k; iteration; Sequential; OpenMP; OpenMP-Tasks; Optimized; Optimized2" > benchmarklow.txt

    for THREADS in 1 2
    do
        for k in 1 10 20 30 40 50
        do
	    for count in {1..3}
	    do
		echo "$THREADS, $k, $count"
	        echo -n "dna-A1; dna-B1; $THREADS; $k;$count" >> benchmarklow.txt
		#echo "" >> benchmarklow.txt
		OMP_NUM_THREADS=$THREADS ./ex2 input1.txt input2.txt $k true >> benchmarklow.txt
		echo "" >> benchmarklow.txt
            done
	done
    done


