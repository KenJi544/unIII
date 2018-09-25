/* ===
Aceste exemplu ilustriaza modalitatea de utilizare a rutinelor "omp_set_dynamic()"   si "omp_get_dynamic()"
===*/
#include <stdio.h>
 #include <omp.h>
 int main(int argc, char *argv[])
 {
   printf("Valoarea  initiala (prestabilita) a variabilei de mediu OMP_DYNAMIC: %d\n", omp_get_dynamic());
   omp_set_dynamic(0);
   printf("Valoarea variabilei de mediu dupa executarea rutinei omp_set_dynamic() OMP_DYNAMIC : %d\n", omp_get_dynamic());
 #pragma omp parallel num_threads(128)
   {
 #pragma omp master
      {
         printf("Regiunea paralela contine, %d fire\n",
                 omp_get_num_threads());
      }
   }
 }

/*
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exemplu3.4.2.exe Exemplu3.4.2.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu3.4.2.exe
Valoarea  initiala (prestabilita) a variabilei de mediu OMP_DYNAMIC: 0
Valoarea variabilei de mediu dupa executarea rutinei omp_set_dynamic() OMP_DYNAMIC : 1
Regiunea paralela contine, 4 fire
[Hancu_B_S@hpc Open_MP]$ 
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpiCC -fopenmp -o Exemplu3.4.2.exe Exemplu3.4.2.cpp
[Hancu_B_S@hpc Open_MP]$ /opt/openmpi/bin/mpirun -n 1 -host compute-0-0,compute-0-1 Exemplu3.4.2.exe
Valoarea  initiala (prestabilita) a variabilei de mediu OMP_DYNAMIC: 0
Valoarea variabilei de mediu dupa executarea rutinei omp_set_dynamic() OMP_DYNAMIC : 0
Regiunea paralela contine, 128 fire
[Hancu_B_S@hpc Open_MP]$ 

*/
