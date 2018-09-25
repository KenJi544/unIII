#include <stdio.h>
#include <omp.h>
#include <iostream>
#define N 1000
main ()
{
int i,iam;
float a[N], b[N], c[N];
/* Some initializations */
for (i=0; i < N; i++)
a[i] = b[i] = i * 1.0;
#pragma omp parallel shared(a,b,c) private(i,iam)
{
#pragma omp sections nowait
{
sleep(omp_get_thread_num());
#pragma omp section
{
iam = omp_get_thread_num(); 
for (i=0; i < N/2; i++)
c[i] = a[i] + b[i];
printf("Procesul OpenMP cu numarul %d, a determinat %d elemente ale vectorului \n", iam, N/2);
}
#pragma omp section
{
iam = omp_get_thread_num(); 
for (i=N/2; i < N; i++)
c[i] = a[i] + b[i];
printf("Procesul OpenMP cu numarul %d, a determinat %d elemente ale vectorului \n", iam, N/2);
}
} /* end of sections */
} /* end of parallel section */
}
/* 
Se genereaza 4 fire.
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exemplu1.2.2.exe Exemplu1.2.2.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu1.2.2.exe
Procesul OpenMP cu numarul 2, a determinat 500 elemente ale vectorului 
Procesul OpenMP cu numarul 3, a determinat 500 elemente ale vectorului 
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu1.2.2.exe
Procesul OpenMP cu numarul 2, a determinat 500 elemente ale vectorului 
Procesul OpenMP cu numarul 3, a determinat 500 elemente ale vectorului 
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu1.2.2.exe
Procesul OpenMP cu numarul 2, a determinat 500 elemente ale vectorului 
Procesul OpenMP cu numarul 3, a determinat 500 elemente ale vectorului 
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu1.2.2.exe
Procesul OpenMP cu numarul 0, a determinat 500 elemente ale vectorului 
Procesul OpenMP cu numarul 1, a determinat 500 elemente ale vectorului 
[Hancu_B_S@hpc Open_MP]$ 


*/
