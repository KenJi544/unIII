
/*
In acest program se calculeaza prin metoda dreptunghiurilor integrala definita pe segmentul [a,b] 
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
#endif
double f(double y) {return(4.0/(1.0+y*y));}

int main()
{
double w, x, sum, pi,a,b;
int i,MPIrank;
int n = 1000000;
int Nodes=1;
MPIrank=0;
w = 1.0/n;
sum = 0.0;
a=(MPIrank+0.0)/Nodes;
b=(MPIrank+1.0)/Nodes;
omp_set_num_threads(2);
#pragma omp parallel private(x) shared(w,a,b) reduction(+:sum)
{
#pragma omp master 
{
printf("Pentru fiecare proces MPI se genereaza %d procese OpenMP (fire)\n", omp_get_num_threads());	
}
#pragma omp for nowait 
for(i=0; i < n; i++)
{
x = a+(b-a)*w*(i-0.5);
sum = sum + f(x);
}
sleep(omp_get_thread_num());
printf("Procesul OpenMP cu numarul %d, a determinat integrala egala cu %f\n", omp_get_thread_num(),(b-a)*w*sum);
}
pi = (b-a)*w*sum;
printf("Valoare finala , pi = %f\n", pi);
}
/*
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Integrala_OpenMP.exe Integrala_OpenMP.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Integrala_OpenMP.exe
Pentru fiecare proces MPI se genereaza 4 procese OpenMP (fire)
Procesul OpenMP cu numarul 0, a determinat integrala egala cu 0.979915
Procesul OpenMP cu numarul 1, a determinat integrala egala cu 0.874676
Procesul OpenMP cu numarul 2, a determinat integrala egala cu 0.719415
Procesul OpenMP cu numarul 3, a determinat integrala egala cu 0.567589
Valoare finala , pi = 3.141595
[Hancu_B_S@hpc Open_MP]$ 
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Integrala_OpenMP.exe Integrala_OpenMP.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Integrala_OpenMP.exe
Pentru fiecare proces MPI se genereaza 2 procese OpenMP (fire)
Procesul OpenMP cu numarul 0, a determinat integrala egala cu 1.854591
Procesul OpenMP cu numarul 1, a determinat integrala egala cu 1.287003
Valoare finala , pi = 3.141595
[Hancu_B_S@hpc Open_MP]$ 

*/
