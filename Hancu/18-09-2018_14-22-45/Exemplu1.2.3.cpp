/*
In acest exemplu se ilustreaza modul de gestionare la nivel de program a sectiunilor critice 
*/

#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
int x,i;
x=0;
omp_set_num_threads(2);
	#pragma omp parallel shared(x) private(i)
	{
	 for(i =0;i<1000;i++)
	  {
		//#pragma omp critical  //cand se eclude aceasta directiva rez. nu sunt corecte
		{
		x=x+1;
		}
	  }
	}
printf("Valoarea lui x=%d \n", x);
}
/*
Cazul cand se utilizeaza directiva #pragma omp critical 
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exemplu1.2.3.exe Exemplu1.2.3.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu1.2.3.exe
Valoarea lui x=2000 
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu1.2.3.exe
Valoarea lui x=2000 
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 2 -host compute-0-0,compute-0-1 Exemplu1.2.3.exe
Valoarea lui x=2000 
Valoarea lui x=2000 
[Hancu_B_S@hpc Open_MP]$ 
Cazul cand nu se utilizeaza directiva #pragma omp critical
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exemplu1.2.3.exe Exemplu1.2.3.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu1.2.3.exe
Valoarea lui x=1492 
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu1.2.3.exe
Valoarea lui x=1127 
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 2 -host compute-0-0,compute-0-1 Exemplu1.2.3.exe
Valoarea lui x=1128 
Valoarea lui x=1118 
[Hancu_B_S@hpc Open_MP]$ 

*/
