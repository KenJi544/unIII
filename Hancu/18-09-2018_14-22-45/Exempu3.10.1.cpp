/*  Acest program genereaza diferite regiuni paralele de tip fire de executie in dependenta 
    de numele nodului pe care se executa aplicatia ! Programul se executa pe nodurile "compute-0-4,compute-0-5". 
*/
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
   (void) omp_set_num_threads(4);// se fixeza numarul de fire pentru fiecare procesor fizic
#endif
//=======
 int numprocs, realnumprocs,rank, namelen,mpisupport;
 char processor_name[MPI_MAX_PROCESSOR_NAME];
 int iam = 0, np = 1;
omp_lock_t lock;
omp_init_lock(&lock);
//omp_init_lock(&lock1);
//omp_init_lock(&lock2);
  MPI_Init(&argc, &argv);
//MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE,&mpisupport);
  MPI_Get_processor_name(processor_name, &namelen);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
      
if (strcmp(processor_name,"compute-0-0.local")==0)
{      
 omp_set_num_threads(4);  

       #pragma omp parallel default(shared) private(iam, np,realnumprocs)
       {                                    //begin parallel construct
        np = omp_get_num_threads();         //returneaza numarul total de fire
        realnumprocs = omp_get_num_procs(); //returneaza numarul de procesoare disponibile
        iam = omp_get_thread_num();         //returneaza 'eticheta" firului     
	omp_set_lock(&lock);		
		#pragma omp master
      		{
		 printf("\n");
      		 printf("    ===Procesul MPI cu rankul %d al nodului cu numele '%s' a executat %d fire ===  \
                 \n",rank,processor_name,omp_get_num_threads());
     		 }   
		//#pragma omp barrier 
//omp_unset_lock(&lock1);  
          //  omp_set_lock(&lock);	
        printf("Hello from thread number %d,total number of theads are %d, MPI process rank is %d, real number"
               " processors is %d on node %s\n", iam, np, rank, realnumprocs, processor_name);

	omp_unset_lock(&lock);      
 	}                                //end parallel construct

 /*      printf("    ===Sfarsitul regiunii paralele generata de rocesul MPI cu rankul %d al nodului cu numele" 
              "'%s'\n",rank,processor_name); 
*/
		
omp_destroy_lock(&lock);
MPI_Barrier(MPI_COMM_WORLD); 
}
 else 
{ 
if (strcmp(processor_name,"compute-0-1.local")==0)
{      
 omp_set_num_threads(2);  

       #pragma omp parallel default(shared) private(iam, np,realnumprocs)
       {                                    //begin parallel construct
        np = omp_get_num_threads();         //returneaza numarul total de fire
        realnumprocs = omp_get_num_procs(); //returneaza numarul de procesoare disponibile
        iam = omp_get_thread_num();         //returneaza 'eticheta" firului  
	omp_set_lock(&lock);		
		#pragma omp master
      		{
		 printf("\n");
      		 printf("    ===Procesul MPI cu rankul %d al nodului cu numele '%s' a executat %d fire ===  \
                 \n",rank,processor_name,omp_get_num_threads());
     		 }   
//omp_unset_lock(&lock1); 
		//#pragma omp barrier   
omp_unset_lock(&lock);                
       		 printf("Hello from thread number %d,total number of theads are %d, MPI process rank is %d, real number"
               " processors is %d on node %s\n", iam, np, rank, realnumprocs, processor_name);
	omp_unset_lock(&lock);  
      }                                //end parallel construct
/*
       printf("    ===sfarsitul regiunii paralele generata de rocesul MPI cu rankul %d al nodului cu numele"
              "'%s'\n",rank,processor_name); 
*/
		
}
omp_destroy_lock(&lock);
//omp_destroy_lock(&lock1);
//omp_destroy_lock(&lock1);
MPI_Barrier(MPI_COMM_WORLD);                  
}  
  MPI_Finalize();
 return 0;
}
/*
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exempu3.10.1.exe Exempu3.10.1.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 2 -host compute-0-0,compute-0-1 Exempu3.10.1.exe

    ===Procesul MPI cu rankul 1 al nodului cu numele 'compute-0-1.local' a executat 2 fire ===                   
Hello from thread number 1,total number of theads are 2, MPI process rank is 1, real number processors is 4 on node compute-0-1.local
Hello from thread number 0,total number of theads are 2, MPI process rank is 1, real number processors is 4 on node compute-0-1.local

    ===Procesul MPI cu rankul 0 al nodului cu numele 'compute-0-0.local' a executat 4 fire ===                   
Hello from thread number 0,total number of theads are 4, MPI process rank is 0, real number processors is 4 on node compute-0-0.local
Hello from thread number 1,total number of theads are 4, MPI process rank is 0, real number processors is 4 on node compute-0-0.local
Hello from thread number 3,total number of theads are 4, MPI process rank is 0, real number processors is 4 on node compute-0-0.local
Hello from thread number 2,total number of theads are 4, MPI process rank is 0, real number processors is 4 on node compute-0-0.local
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exempu3.10.1.exe

    ===Procesul MPI cu rankul 0 al nodului cu numele 'compute-0-0.local' a executat 4 fire ===                   
Hello from thread number 0,total number of theads are 4, MPI process rank is 0, real number processors is 4 on node compute-0-0.local
Hello from thread number 1,total number of theads are 4, MPI process rank is 0, real number processors is 4 on node compute-0-0.local
Hello from thread number 3,total number of theads are 4, MPI process rank is 0, real number processors is 4 on node compute-0-0.local
Hello from thread number 2,total number of theads are 4, MPI process rank is 0, real number processors is 4 on node compute-0-0.local
[Hancu_B_S@hpc Open_MP]$ 

*/
