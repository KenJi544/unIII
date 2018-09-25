/*
Acest Program exemplifica modul de utilizare a rutinelor
a) omp_get_num_threads()-returneazǎ numǎrul de fire care sunt în fasciculul curent
b) omp_set_num_threads()- seteazǎ numǎrul de fire care vor fi utilizate în regiunea
paralela.
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#ifdef _OPENMP
  #include <omp.h>
  #define TRUE  1
  #define FALSE 0
#else
  #define omp_get_thread_num() 0
  #define omp_get_num_threads() 1
#endif

int main()
{
   int TID;

#ifdef _OPENMP
   (void) omp_set_dynamic(1);
   if (omp_get_dynamic()) {printf("Warning: dynamic adjustment of threads has been set\n");}
 //  (void) omp_set_num_threads(4);
#endif

   for (int n=5; n<11; n+=5)
   { 
#pragma omp parallel if (n > 5) num_threads(n) default(none) \
        private(TID) shared(n)
   {
     TID = omp_get_thread_num();
#pragma omp single
     {
       printf("Value of n = %d\n",n);
       printf("Number of threads in parallel region: %d\n", omp_get_num_threads());
     }
sleep(omp_get_thread_num());
     printf("Print statement executed by thread %d\n",TID);
   }  /*-- End of parallel region --*/
   }

   return(0);
}
 /*  ===Cazul cand (void) omp_set_dynamic(0)- desabiliteazǎ ajustarea dinamicǎ (de
sistemul de executie) a numǎrului de fire disponibile pentru executarea regiunilor paralele.
=====
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exemplu3.2.1.exe Exemplu3.2.1.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu3.2.1.exe
Value of n = 5
Number of threads in parallel region: 1
Print statement executed by thread 0
Value of n = 10
Number of threads in parallel region: 10
Print statement executed by thread 0
Print statement executed by thread 1
Print statement executed by thread 2
Print statement executed by thread 3
Print statement executed by thread 4
Print statement executed by thread 5
Print statement executed by thread 6
Print statement executed by thread 7
Print statement executed by thread 8
Print statement executed by thread 9
[Hancu_B_S@hpc Open_MP]$ 
===Cazul cand (void) omp_set_dynamic(1)-abiliteazǎ s ajustarea dinamicǎ (de
sistemul de executie) a numǎrului de fire disponibile pentru executarea regiunilor paralele.
===
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exemplu3.2.1.exe Exemplu3.2.1.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu3.2.1.exe
Warning: dynamic adjustment of threads has been set
Value of n = 5
Number of threads in parallel region: 1
Print statement executed by thread 0
Value of n = 10
Number of threads in parallel region: 4
Print statement executed by thread 0
Print statement executed by thread 1
Print statement executed by thread 2
Print statement executed by thread 3

[Hancu_B_S@hpc Open_MP]$ 

*/  
 
