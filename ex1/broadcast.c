#include "mpi.h"

#include <stdio.h>
#include <string.h>

int main (int argc, char**argv){
	MPI_Init(&argc, &argv);

	int rank, size;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//printf("rank: %d size: %d \n", rank, size);
	
	int length;
	char buf[256];
	
	if( rank == 0 ){
		length = strlen(argv[1]);
		MPI_Bcast(argv[1], length, MPI_CHAR, 0,
MPI_COMM_WORLD);

	
	} else {
		MPI_Bcast(&buf, 256, MPI_CHAR, 0, MPI_COMM_WORLD);
		if( rank == size-1) {
			printf( "i'm node %d receved msg: %s \n",rank, 
buf);

		}


	}

	MPI_Finalize();
	return 0;


}
