#include <omp.h>
#include <mpi.h>
#include <stdio.h>
#include <iostream>
#define _NUM_THREADS 2
int main (int argc, char *argv[]) 
{
int my_rank,namelen;
char processor_name[MPI_MAX_PROCESSOR_NAME];
omp_set_num_threads(_NUM_THREADS);
MPI_Init(&argc, &argv);
MPI_Get_processor_name(processor_name,&namelen);
MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
int c=0, Sum_c;
	#pragma omp parallel reduction(+:c)
	{
	c = 1;
	}
printf("The count of threads on the MPI process %d of the compute node '--%s--' is %d \n", my_rank, processor_name,c);
MPI_Reduce(&c, &Sum_c, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
if (my_rank == 0)
printf("Total number of threads=%d \n", Sum_c);
MPI_Barrier(MPI_COMM_WORLD);
MPI_Finalize();
return 0;
}
