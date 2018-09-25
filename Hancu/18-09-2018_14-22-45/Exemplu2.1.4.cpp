/*
In acest exemlu se ilustreaza modul de utilizare a variabileleo de tip "lasttprivate"
*/
#include <stdio.h>
#include <omp.h>
#include <iostream>
int main(int argc, char *argv[])
{
int n=0;
printf("Valoarea n in zona secventiala a programului (inainte de constructorul paralel): %d\n", n);
   #pragma omp parallel
   {
     #pragma omp sections lastprivate(n)
     {
	sleep(omp_get_thread_num());
	#pragma omp section
	{
printf("Valoarea n pentru firul %d (in #pragma omp section-pana la initializare): %d\n",omp_get_thread_num(), n);
	n=1;
printf("Valoarea n pentru firul %d (in #pragma omp section-dupa initializare): %d\n",omp_get_thread_num(), n);
	}
	#pragma omp section
	{
printf("Valoarea n pentru firul %d (in #pragma omp section- pana la initializare): %d\n",omp_get_thread_num(), n);
	n=2;
printf("Valoarea n pentru firul %d (in #pragma omp section- dupa initializare): %d\n",omp_get_thread_num(), n);
	}
	#pragma omp section
	{
printf("Valoarea n pentru firul %d (in #pragma omp section-pana la initializare): %d\n",omp_get_thread_num(), n);
	n=3;
printf("Valoarea n pentru firul %d (in #pragma omp section-dupa initializare): %d\n",omp_get_thread_num(), n);
        }
     }
sleep(omp_get_thread_num());
   printf("Valoarea n pentru firul %d: %d (dupa #pragma omp section)\n",omp_get_thread_num(), n);
   }
printf("Valoarea n in zona secventiala a programului(dupa constructorul paralel): %d\n", n);
}

/* Se genereaza 4 fire.
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exemplu2.1.3.exe Exemplu2.1.3.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu2.1.3.exe
Valoarea n in zona secventiala a programului (inainte de constructorul paralel): 0
Valoarea n pentru firul 1 (in #pragma omp section-pana la initializare): -1
Valoarea n pentru firul 1 (in #pragma omp section-dupa initializare): 1
Valoarea n pentru firul 3 (in #pragma omp section-pana la initializare): 0
Valoarea n pentru firul 3 (in #pragma omp section-dupa initializare): 3
Valoarea n pentru firul 0 (in #pragma omp section- pana la initializare): 0
Valoarea n pentru firul 0 (in #pragma omp section- dupa initializare): 2
Valoarea n pentru firul 0: 3 (dupa #pragma omp section)
Valoarea n pentru firul 1: 3 (dupa #pragma omp section)
Valoarea n pentru firul 2: 3 (dupa #pragma omp section)
Valoarea n pentru firul 3: 3 (dupa #pragma omp section)
Valoarea n in zona secventiala a programului(dupa constructorul paralel): 3
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu2.1.3.exe
Valoarea n in zona secventiala a programului (inainte de constructorul paralel): 0
Valoarea n pentru firul 3 (in #pragma omp section-pana la initializare): 0
Valoarea n pentru firul 3 (in #pragma omp section-dupa initializare): 1
Valoarea n pentru firul 0 (in #pragma omp section- pana la initializare): 0
Valoarea n pentru firul 0 (in #pragma omp section- dupa initializare): 2
Valoarea n pentru firul 3 (in #pragma omp section-pana la initializare): 1
Valoarea n pentru firul 3 (in #pragma omp section-dupa initializare): 3
Valoarea n pentru firul 0: 3 (dupa #pragma omp section)
Valoarea n pentru firul 1: 3 (dupa #pragma omp section)
Valoarea n pentru firul 2: 3 (dupa #pragma omp section)
Valoarea n pentru firul 3: 3 (dupa #pragma omp section)
Valoarea n in zona secventiala a programului(dupa constructorul paralel): 3
[Hancu_B_S@hpc Open_MP]$ 

Concluzie: In regiune paralela (pana la initializare) valoarea lun n nu este determinata, la iesirea din regiunea paralela valoare lui n este egala cu ultima valoare initializata

*/
