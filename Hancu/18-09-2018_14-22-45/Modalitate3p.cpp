#include <stdio.h>
#include "mpi.h"
//=====
#ifdef _OPENMP
   #include <omp.h>
   #define TRUE  1
   #define FALSE 0
#else
   #define omp_get_thread_num() 0
#endif
int main(int argc, char *argv[])
{
//====
#ifdef _OPENMP
   (void) omp_set_dynamic(FALSE);
   if (omp_get_dynamic()) {printf("Warning: dynamic adjustment of threads has been set\n");}
   (void) omp_set_num_threads(4);
#endif
int required = MPI_THREAD_MULTIPLE;
//int required = MPI_THREAD_SINGLE;
int mpi_rank, mpi_size, provided,j,ithread,namelen;
MPI_Status status; 
char processor_name[MPI_MAX_PROCESSOR_NAME];
//MPI_Init(&argc, &argv);
MPI_Init_thread(&argc, &argv, required, &provided);
MPI_Get_processor_name(processor_name, &namelen);
MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
MPI_Query_thread(&provided);
if (provided <required)
{
    printf("ERROR: The MPI library does not have full thread support\n");
    MPI_Abort(MPI_COMM_WORLD, 1);
}
if (mpi_rank == 0)
 {
  switch (provided) 
  {
  case MPI_THREAD_SINGLE: /* */ break;
  case MPI_THREAD_FUNNELED: /* */ break;
  case MPI_THREAD_SERIALIZED: /* */ break;
  case MPI_THREAD_MULTIPLE: /* */ break;
  default: /* */ break;
  }
printf("===== The provided level of thread support: %d \n",provided);
 }
 

#pragma omp parallel 
  {
	ithread = omp_get_thread_num(); 
//#pragma omp barrier
#pragma omp master
{
	if(mpi_rank==0) 
{ 
	 MPI_Send(&ithread,1,MPI_INT, 1, ithread, MPI_COMM_WORLD);
}
	else{
	MPI_Recv(&j,1,MPI_INT, 0, ithread,MPI_COMM_WORLD,&status);
 printf("The thread number  %d of the MPI proc num %d@%s rcvd=%d from thread number  %d of the MPI proc %d@%s\n",ithread,mpi_rank, processor_name, j,ithread,mpi_rank-1, processor_name); 
	}
}
//#pragma omp barrier
  }
MPI_Finalize();
return 0;
}
/*
=================================
Veriunea MPI suporta numai MPI_THREAD_SINGLE(!) deoarece OpenMPI are versiune  1.4.3
 (executa comanda ompi_info)
=====================================
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Modalitate3p.exe Modalitate3p.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 2 -host compute-0-0,compute-0-1 Modalitate3p.exe
===== The provided level of thread support: 0 
The thread number  3 of the MPI proc num 1@compute-0-1.local rcvd=0 from thread number  3 of the MPI proc 0@compute-0-1.local
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 2 -host compute-0-0,compute-0-1 Modalitate3p.exe
===== The provided level of thread support: 0 
The thread number  2 of the MPI proc num 1@compute-0-1.local rcvd=2 from thread number  2 of the MPI proc 0@compute-0-1.local
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 2 -host compute-0-0,compute-0-1 Modalitate3p.exe
===== The provided level of thread support: 0 
The thread number  1 of the MPI proc num 1@compute-0-1.local rcvd=2 from thread number  1 of the MPI proc 0@compute-0-1.local
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 2 -host compute-0-0,compute-0-1 Modalitate3p.exe
===== The provided level of thread support: 0 
The thread number  3 of the MPI proc num 1@compute-0-1.local rcvd=1 from thread number  3 of the MPI proc 0@compute-0-1.local
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 2 -host compute-0-0,compute-0-1 Modalitate3p.exe
===== The provided level of thread support: 0 
The thread number  3 of the MPI proc num 1@compute-0-1.local rcvd=3 from thread number  3 of the MPI proc 0@compute-0-1.local
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 2 -host compute-0-0,compute-0-1 Modalitate3p.exe
===== The provided level of thread support: 0 
The thread number  2 of the MPI proc num 1@compute-0-1.local rcvd=0 from thread number  2 of the MPI proc 0@compute-0-1.local
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 2 -host compute-0-0,compute-0-1 Modalitate3p.exe
===== The provided level of thread support: 0 
The thread number  3 of the MPI proc num 1@compute-0-1.local rcvd=0 from thread number  3 of the MPI proc 0@compute-0-1.local
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 2 -host compute-0-0,compute-0-1 Modalitate3p.exe
===== The provided level of thread support: 0 
The thread number  0 of the MPI proc num 1@compute-0-1.local rcvd=0 from thread number  0 of the MPI proc 0@compute-0-1.local
[Hancu_B_S@hpc Open_MP]$ 

*/
