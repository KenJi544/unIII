/*
 Exemplu 1.2.1 Sa se elaboreze un program OpenMP in care se determina suma a doi vectori. Firele vor calcula cite 100 de elemente ale vectorului. Sa se determine cate elemente ale vectorului suma vor fi determinate de fiecare fir in parte.
*/
#include <omp.h>
#include<stdio.h>
#include <iostream>
#define CHUNKSIZE 100
#define N 1000
main ()
{
int i, k,chunk,iam;
float a[N], b[N], c[N];
/* initializare vectorilor  */
for (i=0; i < N; i++)
a[i] = b[i] = i * 1.0;
chunk = CHUNKSIZE;
#pragma omp parallel shared(a,b,c,chunk) private(i,k,iam)
{
k=0;
iam = omp_get_thread_num();  
#pragma omp for schedule(static,chunk) nowait
for (i=0; i < N; i++)
{
c[i] = a[i] + b[i];
k=k+1;
}
sleep(iam);
printf("Procesul OpenMP cu numarul %d, a determinat %d elemente ale vectorului \n", iam, k);
} // sfarsitul constructorului paralel
return 0;
}

/*
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exemplu1.2.1.exe Exemplu1.2.1.cpp
===Cazul ...schedule(dynamic,chunk)... 
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu1.2.1.exe
Procesul OpenMP cu numarul 0, a determinat 500 elemente ale vectorului 
Procesul OpenMP cu numarul 1, a determinat 400 elemente ale vectorului 
Procesul OpenMP cu numarul 2, a determinat 100 elemente ale vectorului 
Procesul OpenMP cu numarul 3, a determinat 0 elemente ale vectorului 
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu1.2.1.exe
Procesul OpenMP cu numarul 0, a determinat 500 elemente ale vectorului 
Procesul OpenMP cu numarul 1, a determinat 400 elemente ale vectorului 
Procesul OpenMP cu numarul 2, a determinat 0 elemente ale vectorului 
Procesul OpenMP cu numarul 3, a determinat 100 elemente ale vectorului 
[Hancu_B_S@hpc Open_MP]$ 
 [Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exemplu1.2.1.exe Exemplu1.2.1.cpp
===Cazul ...schedule(static,chunk)... 
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu1.2.1.exe
Procesul OpenMP cu numarul 0, a determinat 300 elemente ale vectorului 
Procesul OpenMP cu numarul 1, a determinat 300 elemente ale vectorului 
Procesul OpenMP cu numarul 2, a determinat 200 elemente ale vectorului 
Procesul OpenMP cu numarul 3, a determinat 200 elemente ale vectorului 
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu1.2.1.exe
Procesul OpenMP cu numarul 0, a determinat 300 elemente ale vectorului 
Procesul OpenMP cu numarul 1, a determinat 300 elemente ale vectorului 
Procesul OpenMP cu numarul 2, a determinat 200 elemente ale vectorului 
Procesul OpenMP cu numarul 3, a determinat 200 elemente ale vectorului 
[Hancu_B_S@hpc Open_MP]$ 

*/
