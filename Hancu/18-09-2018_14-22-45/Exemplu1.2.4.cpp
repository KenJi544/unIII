/*
In acest exemplu se ilusteraza modul de utilizare a directivei "threadprivate"
*/
#include <stdio.h>
#include <omp.h> 
#include <iostream>
int  a, b, i, tid;
float x;
#pragma omp threadprivate(a, x)
main ()  
{
/* Explicitly turn off dynamic threads */
  omp_set_dynamic(0);
  printf("Prima regiune paralela:\n");
#pragma omp parallel private(b,tid)
  {
  tid = omp_get_thread_num();
  a = tid;
  b = tid;
  x = 1.1 * tid +1.0;
sleep(omp_get_thread_num());
  printf("Procesul OpenMP %d:   a,b,x= %d %d %f\n",tid,a,b,x);
  }  /* end of parallel section */
  printf("************************************\n");
  printf("Aici firul Master executa un cod serial\n");
  printf("************************************\n");
  printf("A doua regiune paralela:\n");
#pragma omp parallel private(tid)
  {
  tid = omp_get_thread_num();
sleep(omp_get_thread_num());
  printf("Procesul OpenMP %d:   a,b,x= %d %d %f\n",tid,a,b,x);
  }  /* end of parallel section */
}
/* Se genereaza 4 fire
[[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exemplu1.2.4.exe Exemplu1.2.4.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu1.2.4.exe
Prima regiune paralela:
Procesul OpenMP 0:   a,b,x= 0 0 1.000000
Procesul OpenMP 1:   a,b,x= 1 1 2.100000
Procesul OpenMP 2:   a,b,x= 2 2 3.200000
Procesul OpenMP 3:   a,b,x= 3 3 4.300000
************************************
Aici firul Master executa un cod serial
************************************
A doua regiune paralela:
Procesul OpenMP 0:   a,b,x= 0 0 1.000000
Procesul OpenMP 1:   a,b,x= 1 0 2.100000
Procesul OpenMP 2:   a,b,x= 2 0 3.200000
Procesul OpenMP 3:   a,b,x= 3 0 4.300000
[Hancu_B_S@hpc Open_MP]$ 

====Comentariu:
Se observa ca valorile variabilelor a si x se pasteaza si in a doua regiune paralela, pe cand variabila b nu este determinata
*/
