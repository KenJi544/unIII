/*
In acest exemplu se ilustreaza modalitatea de utilizare a rutinelor omp_init_lock(),omp_set_lock(),omp_unset_lock si 
omp_destroy_lock
*/
#include <stdio.h>
#include <omp.h>
#include <iostream>
omp_lock_t lock,lock1;
int main(int argc, char *argv[])
{
int n;
omp_init_lock(&lock);
omp_init_lock(&lock1);
omp_set_num_threads(3);
#pragma omp parallel private (n)
	{
omp_set_lock(&lock1);
#pragma omp master 
{
printf("Se genereaza %d procese OpenMP (fire)\n", omp_get_num_threads());	
}
omp_unset_lock(&lock1);
	n=omp_get_thread_num();
	omp_set_lock(&lock);
        printf("=================\n");
	printf("Inceputul sectiei inchise, firul %d\n", n);
sleep(3);
	printf("Sfarsitul sectiei inchise, firul %d\n", n);
        printf("=================\n");
		printf("\n");
	omp_unset_lock(&lock);
	}
omp_destroy_lock(&lock1);
omp_destroy_lock(&lock);
}
/*
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exemplu3.6.2.exe Exemplu3.6.2.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu3.6.2.exe
Se genereaza 3 procese OpenMP (fire)
=================
Inceputul sectiei inchise, firul 0
Sfarsitul sectiei inchise, firul 0
=================

=================
Inceputul sectiei inchise, firul 2
Sfarsitul sectiei inchise, firul 2
=================

=================
Inceputul sectiei inchise, firul 1
Sfarsitul sectiei inchise, firul 1
=================



[Hancu_B_S@hpc Open_MP]$ 

*/
