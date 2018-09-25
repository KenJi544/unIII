/*
Acest Program exemplifica modul de utilizare a rutine omp_in_parallel()
*/

#include <stdio.h>
#include <omp.h>
void mode(void)
{
if(omp_in_parallel()) printf("Se executa instructiuni din regiunea paralela\n");
else printf("Se executa instructiuni din regiunea segventiala\n");
}
int main(int argc, char *argv[])
{
mode();
  #pragma omp parallel
  {
#pragma omp master
{
mode();
}
  }
}
/*
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exemplu3.4.1.exe Exemplu3.4.1.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu3.4.1.exe
Se executa instructiuni din regiunea segventiala
Se executa instructiuni din regiunea paralela
[Hancu_B_S@hpc Open_MP]$ 

*/
