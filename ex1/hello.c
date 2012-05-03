* -*  *  *  *  *  *  *  *  *  *  *  *
*   Marcel Karsten -- 343619,
*   Patrick Lorenz -- 341922,
*   Richard Klemm -- 343635
*  *  *  *  *  *  *  *  *  *  *  *  */

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
		MPI_Send(argv[1], length, MPI_CHAR, 1, 42, MPI_COMM_WORLD);
	} else {
		MPI_Recv(&buf, 256, MPI_CHAR, rank-1, 42, MPI_COMM_WORLD, NULL);
		if( rank != size-1 ){
			length = strlen( buf );
			MPI_Send(argv[1], length, MPI_CHAR, rank+1, 42, MPI_COMM_WORLD);
		} else {
			printf( "i'm node %d receved msg: %s \n",rank, buf);
		}
	}

	MPI_Finalize();
	return 0;
}
