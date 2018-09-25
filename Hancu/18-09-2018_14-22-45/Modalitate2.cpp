#include <omp.h>
#include "mpi.h"
#define _NUM_THREADS 2
int main (int argc, char *argv[]) 
{
int p,my_rank,namelen;
char processor_name[MPI_MAX_PROCESSOR_NAME];
/* set number of threads to spawn */
omp_set_num_threads(_NUM_THREADS);
/* initialize MPI stuff */
MPI_Init(&argc, &argv);
MPI_Get_processor_name(processor_name,&namelen);
MPI_Comm_size(MPI_COMM_WORLD,&p);
MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
/* the following is a parallel OpenMP
* executed by each MPI process
*/
#pragma omp parallel
{
#pragma omp master
{
// some MPI_ call as an MPI process
 MPI_Get_processor_name(processor_name,&namelen);
 printf("Hello, I am the process number %d on the compute hostname %s , from total number of  process %d\n",my_rank,    processor_name, p);
}
}
/* finalize MPI */
MPI_Finalize();
return 0;
}
