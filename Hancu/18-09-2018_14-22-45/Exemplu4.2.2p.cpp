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
sleep(my_rank);
#pragma omp parallel 
{
omp_set_lock(&lock);
	#pragma omp master 
      	{
c = omp_get_num_threads();
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
/*
* Aici instructiune de atribiure c = omp_get_num_threads(); se executa de 6 ori 
*
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exemplu4.2.2p.exe Exemplu4.2.2p.cpp 
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 6 -machinefile 1_MPI_per_Nodes Exemplu4.2.2p.exe
    In regiunea paralela curenta s-au generat 2 fire
The count of threads on the MPI process 0 of the compute node '--compute-0-0.local--' is 2 
    In regiunea paralela curenta s-au generat 2 fire
The count of threads on the MPI process 1 of the compute node '--compute-0-1.local--' is 2 
    In regiunea paralela curenta s-au generat 2 fire
The count of threads on the MPI process 2 of the compute node '--compute-0-2.local--' is 2 
    In regiunea paralela curenta s-au generat 2 fire
The count of threads on the MPI process 3 of the compute node '--compute-0-9.local--' is 2 
    In regiunea paralela curenta s-au generat 2 fire
The count of threads on the MPI process 4 of the compute node '--compute-0-10.local--' is 2 
    In regiunea paralela curenta s-au generat 2 fire
The count of threads on the MPI process 5 of the compute node '--compute-0-12.local--' is 2 
Total number of threads=12 

[Hancu_B_S@hpc Open_MP]$ 

*/
