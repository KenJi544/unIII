#include <omp.h>
#include "mpi.h"
#define _NUM_THREADS 2
/* Each MPI process spawns a distinct OpenMP
* master thread; so limit the number of MPI
* processes to one per node
*/
int main (int argc, char *argv[]) 
{
int p,my_rank,namelen;
char processor_name[MPI_MAX_PROCESSOR_NAME];
/* set number of threads to spawn */
omp_set_num_threads(_NUM_THREADS);
omp_lock_t lock;
omp_init_lock(&lock);
/* initialize MPI stuff */
MPI_Init(&argc, &argv);
MPI_Get_processor_name(processor_name, &namelen);
MPI_Comm_size(MPI_COMM_WORLD,&p);
MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
/* the following is a parallel OpenMP
* executed by each MPI process
*/
int c, Sum_c;
#pragma omp parallel reduction(+:c)
{
c = omp_get_num_threads();
omp_set_lock(&lock);
	#pragma omp master
      	{
	 printf("    In regiunea paralela curenta s-au generat %d fire\n",omp_get_num_threads());
   	} 
omp_unset_lock(&lock);
}
/* expect a number to get printed for each MPI process */
printf("The count of threads on the MPI process %d of the compute node '--%s--' is %d \n", my_rank,processor_name,c);
omp_destroy_lock(&lock);
MPI_Reduce(&c, &Sum_c, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
if (my_rank == 0) printf("Total number of threads=%d \n",Sum_c);
MPI_Barrier(MPI_COMM_WORLD);
/* finalize MPI */
MPI_Finalize();
return 0;
}
