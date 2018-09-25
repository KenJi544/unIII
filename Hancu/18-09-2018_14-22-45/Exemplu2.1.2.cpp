/*
In acest exemlu se ilustreaza modul de utilizare a variabileleo de tip "shared"
*/
#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
int i, m[5];
printf("Vectorul m pana la directiva parallel shared:\n");
/* Se initializeaza vectorul m */
for (i=0; i<5; i++){
m[i]=0;
printf("%d\n", m[i]);
}
omp_set_num_threads(2);
#pragma omp parallel shared(m)
	{
	/* Se atribuie valoarea 1 elementului cu indicele egal cu numarul firului din vectorul m */
	m[omp_get_thread_num()]=1;
	}
printf("Valoarea vectorului dupa  directiva parallel shared:\n");
for (i=0; i<5; i++) printf("%d\n", m[i]);
}
/*
[[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exemplu2.1.2.exe Exemplu2.1.2.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu2.1.2.exe
Vectorul m pana la directiva parallel shared:
0
0
0
0
0
Valoarea vectorului dupa  directiva parallel shared:
1
1
0
0
0
[Hancu_B_S@hpc Open_MP]$ 

*/
