#include <omp.h>
#include "mpi.h"
#define _NUM_THREADS 2
int main (int argc, char *argv[]) 
{
int p,my_rank,namelen;
/* set number of threads to spawn */
omp_set_num_threads(_NUM_THREADS);
/* initialize MPI stuff */
char processor_name[MPI_MAX_PROCESSOR_NAME];
MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD,&p);
MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
MPI_Get_processor_name(processor_name,&namelen);
/* the following is a parallel OpenMP
 * executed by each MPI process
*/
  #pragma omp parallel
  {
   // #pragma omp master
    {
    if ( 0 == my_rank)
    // some MPI_ call as ROOT process
    printf("Hello, I am the process number %d on the compute hostname %s , from total number of  process %d\n",my_rank,    processor_name, p);
    else
    // some MPI_ call as non-ROOT process
    printf("Hello, I am the process number %d on the compute hostname %s , from total number of  process %d\n",my_rank,    processor_name, p);
    }
  }
/* expect a number to get printed for each MPI process */
//printf("%d\n",c);
/* finalize MPI */
MPI_Finalize();
return 0;
}
/*
===Cazul #pragma omp master
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Modalitate1.exe Modalitate1.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 2 -host compute-0-0,compute-0-1 Modalitate1.exe
Hello, I am the process number 1 on the compute hostname compute-0-1.local , from total number of  process 2
Hello, I am the process number 0 on the compute hostname compute-0-0.local , from total number of  process 2
===Cazul // #pragma omp master
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Modalitate1.exe Modalitate1.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 2 -host compute-0-0,compute-0-1 Modalitate1.exe
Hello, I am the process number 0 on the compute hostname compute-0-0.local , from total number of  process 2
Hello, I am the process number 1 on the compute hostname compute-0-1.local , from total number of  process 2
Hello, I am the process number 0 on the compute hostname compute-0-0.local , from total number of  process 2
Hello, I am the process number 1 on the compute hostname compute-0-1.local , from total number of  process 2
[Hancu_B_S@hpc Open_MP]$ 

*/
