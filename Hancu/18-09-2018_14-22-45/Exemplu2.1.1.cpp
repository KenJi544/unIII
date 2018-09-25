/*
In acest exemlu se ilustreaza modul de utilizare a variabileleo de tip "private"
*/

#include <stdio.h>
#include <omp.h>
#include <iostream>
int main(int argc, char *argv[])
{
int n=1,iam;
printf("Valoarea lui n pana la directiva parallel cu clauza private: %d\n", n);
#pragma omp parallel private(n,iam)
	{
	sleep(omp_get_thread_num());
	printf("   OpenMP procesul %d-valoarea lui n dupa clauza private: %d\n", omp_get_thread_num(),n);
	n=omp_get_thread_num();
	printf("   OpenMP procesul %d-valoarea lui n dupa initializare de catre fir: %d\n",omp_get_thread_num(), n);
	}
printf("Valoarea lui n dupa directiva parallel cu clauza private: %d\n", n);
}
/* Se genereaza 4 fire.
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exemplu2.1.1.exe Exemplu2.1.1.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu2.1.1.exe
Valoarea lui n pana la directiva parallel cu clauza private: 1
   OpenMP procesul 0-valoarea lui n dupa clauza private: 0
   OpenMP procesul 0-valoarea lui n dupa initializare de catre fir: 0
   OpenMP procesul 1-valoarea lui n dupa clauza private: -1
   OpenMP procesul 1-valoarea lui n dupa initializare de catre fir: 1
   OpenMP procesul 2-valoarea lui n dupa clauza private: 0
   OpenMP procesul 2-valoarea lui n dupa initializare de catre fir: 2
   OpenMP procesul 3-valoarea lui n dupa clauza private: 0
   OpenMP procesul 3-valoarea lui n dupa initializare de catre fir: 3
Valoarea lui n dupa directiva parallel cu clauza private: 1
[Hancu_B_S@hpc Open_MP]$ 


*/
