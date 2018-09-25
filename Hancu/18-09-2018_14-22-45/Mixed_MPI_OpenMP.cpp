#include <stdio.h>
#include "mpi.h"
#include <omp.h>
int main(int argc, char *argv[])
{
 int numprocs, realnumprocs,rank, namelen;
 char processor_name[MPI_MAX_PROCESSOR_NAME];
 int iam = 0, np = 1;
  MPI_Init(&argc, &argv);
  MPI_Get_processor_name(processor_name, &namelen);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 for (int i = 0; i < numprocs; ++i) 
 {
sleep(rank);
     if (rank==i) 
     {
      printf("  \n");
     omp_set_num_threads(numprocs+i);     // se specifica numarul de fire pentru fiecare MPI proces
                                          // care nu va depasi valoarea M, export OMP_NUM_THREADS=M 
    {      
 printf("    ===Procesul MPI cu rankul %d al nodului cu numele '%s' a executat firele ===\n",rank,processor_name); 
       #pragma omp parallel default(shared) private(iam, np,realnumprocs)
       {                                    //begin parallel construct
        np = omp_get_num_threads();         //returneaza numarul total de fire
        realnumprocs = omp_get_num_procs(); //returneaza numarul de procesoare disponibile
        iam = omp_get_thread_num();         //returneaza 'eticheta" firului                      
        printf("Hello from thread number %d,total number of theads are %d, MPI process rank is %d, real number"
               " processors is %d on node %s\n", iam, np, rank, realnumprocs, processor_name);
        }                                //end parallel construct
   }
       printf("    -/-/-/-/-Procesul MPI cu rankul %d a finisat executarea firelor -/-/-/-/-\n", rank);
  
     }                                  // end if    
  
MPI_Barrier(MPI_COMM_WORLD);
 }                                     //end for 


  MPI_Finalize();
 return 0;
}
/*
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Mixed_MPI_OpenMP.exe Mixed_MPI_OpenMP.cpp 
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 2 -host compute-0-0,compute-0-1 Mixed_MPI_OpenMP.exe
  
    ===Procesul MPI cu rankul 0 al nodului cu numele 'compute-0-0.local' a executat firele ===
Hello from thread number 0,total number of theads are 2, MPI process rank is 0, real number processors is 4 on node compute-0-0.local
Hello from thread number 1,total number of theads are 2, MPI process rank is 0, real number processors is 4 on node compute-0-0.local
    -/-/-/-/-Procesul MPI cu rankul 0 a finisat executarea firelor -/-/-/-/-
  
    ===Procesul MPI cu rankul 1 al nodului cu numele 'compute-0-1.local' a executat firele ===
Hello from thread number 0,total number of theads are 3, MPI process rank is 1, real number processors is 4 on node compute-0-1.local
Hello from thread number 1,total number of theads are 3, MPI process rank is 1, real number processors is 4 on node compute-0-1.local
Hello from thread number 2,total number of theads are 3, MPI process rank is 1, real number processors is 4 on node compute-0-1.local
    -/-/-/-/-Procesul MPI cu rankul 1 a finisat executarea firelor -/-/-/-/-
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 3 -host compute-0-0,compute-0-1 Mixed_MPI_OpenMP.exe
  
    ===Procesul MPI cu rankul 0 al nodului cu numele 'compute-0-0.local' a executat firele ===
Hello from thread number 0,total number of theads are 3, MPI process rank is 0, real number processors is 4 on node compute-0-0.local
Hello from thread number 1,total number of theads are 3, MPI process rank is 0, real number processors is 4 on node compute-0-0.local
Hello from thread number 2,total number of theads are 3, MPI process rank is 0, real number processors is 4 on node compute-0-0.local
    -/-/-/-/-Procesul MPI cu rankul 0 a finisat executarea firelor -/-/-/-/-
  
    ===Procesul MPI cu rankul 1 al nodului cu numele 'compute-0-1.local' a executat firele ===
Hello from thread number 0,total number of theads are 4, MPI process rank is 1, real number processors is 4 on node compute-0-1.local
Hello from thread number 1,total number of theads are 4, MPI process rank is 1, real number processors is 4 on node compute-0-1.local
Hello from thread number 3,total number of theads are 4, MPI process rank is 1, real number processors is 4 on node compute-0-1.local
Hello from thread number 2,total number of theads are 4, MPI process rank is 1, real number processors is 4 on node compute-0-1.local
    -/-/-/-/-Procesul MPI cu rankul 1 a finisat executarea firelor -/-/-/-/-
  
    ===Procesul MPI cu rankul 2 al nodului cu numele 'compute-0-0.local' a executat firele ===
Hello from thread number 4,total number of theads are 5, MPI process rank is 2, real number processors is 4 on node compute-0-0.local
Hello from thread number 0,total number of theads are 5, MPI process rank is 2, real number processors is 4 on node compute-0-0.local
Hello from thread number 1,total number of theads are 5, MPI process rank is 2, real number processors is 4 on node compute-0-0.local
Hello from thread number 2,total number of theads are 5, MPI process rank is 2, real number processors is 4 on node compute-0-0.local
Hello from thread number 3,total number of theads are 5, MPI process rank is 2, real number processors is 4 on node compute-0-0.local
    -/-/-/-/-Procesul MPI cu rankul 2 a finisat executarea firelor -/-/-/-/-
[Hancu_B_S@hpc Open_MP]$ 

*/
