
/*
In acest exemplu se ilusreaza modul de utilizare a clauzei "reduction". Se determina produsul scalar a doi vectori
*/
#include <stdio.h>
#include <omp.h>
#include <iostream>
main () 
{
int i, n, chunk,k;
float a[100], b[100], result;
/* Se initializeaza valorile */
n = 100;
chunk = 10;
result = 0.0;
for (i=0; i < n; i++)
{
a[i] = 1;//i * 1.0;
b[i] = 1;//i * 2.0;
}
omp_set_num_threads(2);
	#pragma omp parallel default(shared) private(i,k) reduction(+:result) 
	{	
	k=0;
		#pragma omp for schedule(dynamic,chunk) nowait
		for (i=0; i < n; i++)
		{
		k=k+1;
		result = result + (a[i] * b[i]);
		}
		sleep(omp_get_thread_num());
		printf("Procesul OpenMP cu numarul %d, a determinat %d elemente ale produsului scalar egal cu %f\n", omp_get_thread_num(),k,result);		
		
	}
printf("Produsul scalar este= %f\n",result);
}
/*
===Cazul ...schedule(static,chunk)... 
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exemplu2.1.5.exe Exemplu2.1.5.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu2.1.5.exe
Procesul OpenMP cu numarul 0, a determinat 50 elemente ale produsului scalar egal cu 50.000000
Procesul OpenMP cu numarul 1, a determinat 50 elemente ale produsului scalar egal cu 50.000000
Produsul scalar este= 100.000000
[Hancu_B_S@hpc Open_MP]$ 

===Cazul ...schedule(dynamic,chunk)... 
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exemplu2.1.5.exe Exemplu2.1.5.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu2.1.5.exe
Procesul OpenMP cu numarul 0, a determinat 90 elemente ale produsului scalar egal cu 90.000000
Procesul OpenMP cu numarul 1, a determinat 10 elemente ale produsului scalar egal cu 10.000000
Produsul scalar este= 100.000000

[Hancu_B_S@hpc Open_MP]$ 
*/
