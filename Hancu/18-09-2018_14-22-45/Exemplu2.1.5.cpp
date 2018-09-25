/*
In acest exemplu se ilusreaza modul de utilizare a clauzei "copyin"
*/
#include <stdio.h>
#include <omp.h>
#include <iostream>
int n;
#pragma omp threadprivate(n)
int main(int argc, char *argv[])
{
n=1;
#pragma omp parallel copyin(n)
{
sleep(omp_get_thread_num());
printf("Valoarea n in prima regiune paralela a firului %d: %d\n", omp_get_thread_num(),n);
}
printf("************************************\n");
  printf("Aici firul Master executa un cod serial\n");
  printf("************************************\n");
n=2;
#pragma omp parallel copyin(n)
{
sleep(omp_get_thread_num());
printf("Valoarea n in a doua regiune paralela a firului %d: %d\n", omp_get_thread_num(),n);
}
printf("************************************\n");
  printf("Aici firul Master executa un cod serial\n");
  printf("************************************\n");
#pragma omp parallel 
{
sleep(omp_get_thread_num());
printf("Valoarea n in a treia regiune paralela a firului %d: %d\n", omp_get_thread_num(),n);
}
}

/* Se genereaza 4 fire.
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exemplu2.1.4.exe Exemplu2.1.4.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu2.1.4.exe
Valoarea n in prima regiune paralela a firului 0: 1
Valoarea n in prima regiune paralela a firului 1: 1
Valoarea n in prima regiune paralela a firului 2: 1
Valoarea n in prima regiune paralela a firului 3: 1
************************************
Aici firul Master executa un cod serial
************************************
Valoarea n in a doua regiune paralela a firului 0: 2
Valoarea n in a doua regiune paralela a firului 1: 2
Valoarea n in a doua regiune paralela a firului 2: 2
Valoarea n in a doua regiune paralela a firului 3: 2
************************************
Aici firul Master executa un cod serial
************************************
Valoarea n in a treia regiune paralela a firului 0: 2
Valoarea n in a treia regiune paralela a firului 1: 2
Valoarea n in a treia regiune paralela a firului 2: 2
Valoarea n in a treia regiune paralela a firului 3: 2
[Hancu_B_S@hpc Open_MP]$ 

*/
