#include <mpi.h>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
int main(int argc, char *argv[])
{
int rank,test_rank=2;
int size;
int ndims = 3;    
int source, dest;
int up_y,down_y,right_x,left_x,up_z, down_z;
int dims[3]={0,0,0},coords[3]={0,0,0}; 
int coords_left_x[3]={0,0,0},coords_right_x[3]={0,0,0},
    coords_left_y[3]={0,0,0},coords_right_y[3]={0,0,0},  
    coords_up_z[3]={0,0,0},coords_down_z[3]={0,0,0};  
int periods[3]={0,0,0},reorder = 0;
MPI_Comm comm;
MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Dims_create(size, ndims, dims);
if(rank == 0)
{
printf("\n=====REZULTATUL PROGRAMULUI '%s' \n",argv[0]); 	 	
for ( int i = 0; i < 3; i++ )
cout << "Numarul de procese pe axa "<< i<< " este "<< dims[i] << "; ";
cout << endl;	
}
MPI_Barrier(MPI_COMM_WORLD);
MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, reorder, &comm);
MPI_Cart_coords(comm, rank, ndims, coords);  
sleep(rank);  
cout << "Procesul cu rankul " << rank << " are coordonatele (" << coords[0] << "," << coords[1] << "," << coords[2] <<")"<< endl;   
 MPI_Barrier(MPI_COMM_WORLD);
if(rank == test_rank)
{
printf("Sunt procesul cu rankul %d (%d,%d,%d) vecinii mei sunt: \n",rank,coords[0],coords[1],coords[2]);
MPI_Cart_shift(comm,0,1,&left_x,&right_x);
if (left_x<0) {coords_left_x[0]=-1; coords_left_x[1]=-1;coords_left_x[2]=-1;}
else {MPI_Cart_coords(comm, left_x, ndims, coords_left_x); }
if (right_x<0) {coords_right_x[0]=-1;coords_right_x[1]=-1;coords_right_x[2]=-1;}
else {MPI_Cart_coords(comm, right_x, ndims, coords_right_x); }
printf("   pe directia axei X : stanga %d(%d,%d,%d) dreapta %d(%d,%d,%d) \n",left_x,coords_left_x[0],coords_left_x[1],coords_left_x[2],right_x,coords_right_x[0],coords_right_x[1],coords_right_x[2]);
MPI_Cart_shift(comm,1,1,&up_y,&down_y);
if (up_y<0) {coords_left_y[0]=-1; coords_left_y[1]=-1;coords_left_y[2]=-1;}
else {MPI_Cart_coords(comm, up_y, ndims, coords_left_y); }
if (down_y<0) {coords_right_y[0]=-1;coords_right_y[1]=-1;coords_right_y[2]=-1;}
else {MPI_Cart_coords(comm, down_y, ndims, coords_right_y); }
printf("   pe directia axei Y : stanga %d(%d,%d,%d) dreapta %d(%d,%d,%d) \n",up_y,coords_left_y[0],coords_left_y[1],coords_left_y[2],down_y,coords_right_y[0],coords_right_y[1],coords_right_y[2]);
    MPI_Cart_shift(comm,2,1,&up_z,&down_z);
 if (up_z<0) {coords_up_z[0]=-1; coords_up_z[1]=-1;coords_up_z[2]=-1;}
else {MPI_Cart_coords(comm, up_z, ndims, coords_up_z); }
if (down_z<0) {coords_down_z[0]=-1;coords_down_z[1]=-1;coords_down_z[2]=-1;}
else {MPI_Cart_coords(comm, down_z, ndims, coords_down_z); }
printf("   pe directia axei Z : jos %d(%d,%d,%d) sus %d(%d,%d,%d) \n",up_z,coords_up_z[0],coords_up_z[1],coords_up_z[2],down_z,coords_down_z[0],coords_down_z[1],coords_down_z[2]);   
 printf("Valorile negative semnifica lipsa procesului vecin!\n");
}
MPI_Finalize();
return 0;
}
/*
[Hancu_B_S@hpc Notate_Exemple]$ /opt/openmpi/bin/mpiCC -o Exemplu_3_5_4_new.exe Exemplu_3_5_4_new.cpp
[Hancu_B_S@hpc Notate_Exemple]$ /opt/openmpi/bin/mpirun -n 6  -machinefile ~/nodes6 Exemplu_3_5_4_new.exe

=====REZULTATUL PROGRAMULUI 'Exemplu_3_5_4_new.exe' 
Numarul de procese pe axa 0 este 3; Numarul de procese pe axa 1 este 2; Numarul de procese pe axa 2 este 1; 
Procesul cu rankul 0 are coordonatele (0,0,0)
Procesul cu rankul 1 are coordonatele (0,1,0)
Procesul cu rankul 2 are coordonatele (1,0,0)
Procesul cu rankul 3 are coordonatele (1,1,0)
Procesul cu rankul 4 are coordonatele (2,0,0)
Procesul cu rankul 5 are coordonatele (2,1,0)
Sunt procesul cu rankul 2 (1,0,0) vecinii mei sunt: 
   pe directia axei X : stanga 0(0,0,0) dreapta 4(2,0,0) 
   pe directia axei Y : stanga -2(-1,-1,-1) dreapta 3(1,1,0) 
   pe directia axei Z : jos -2(-1,-1,-1) sus -2(-1,-1,-1) 
Valorile negative semnifica lipsa procesului vecin!
[Hancu_B_S@hpc Notate_Exemple]$ /opt/openmpi/bin/mpirun -n 8  -machinefile ~/nodes6 Exemplu_3_5_4_new.exe

=====REZULTATUL PROGRAMULUI 'Exemplu_3_5_4_new.exe' 
Numarul de procese pe axa 0 este 2; Numarul de procese pe axa 1 este 2; Numarul de procese pe axa 2 este 2; 
Procesul cu rankul 0 are coordonatele (0,0,0)
Procesul cu rankul 1 are coordonatele (0,0,1)
Procesul cu rankul 2 are coordonatele (0,1,0)
Procesul cu rankul 3 are coordonatele (0,1,1)
Procesul cu rankul 4 are coordonatele (1,0,0)
Procesul cu rankul 5 are coordonatele (1,0,1)
Procesul cu rankul 6 are coordonatele (1,1,0)
Procesul cu rankul 7 are coordonatele (1,1,1)
Sunt procesul cu rankul 2 (0,1,0) vecinii mei sunt: 
   pe directia axei X : stanga -2(-1,-1,-1) dreapta 6(1,1,0) 
   pe directia axei Y : stanga 0(0,0,0) dreapta -2(-1,-1,-1) 
   pe directia axei Z : jos -2(-1,-1,-1) sus 3(0,1,1) 
Valorile negative semnifica lipsa procesului vecin!
[Hancu_B_S@hpc Notate_Exemple]$ /opt/openmpi/bin/mpirun -n 27  -machinefile ~/nodes6 Exemplu_3_5_4_new.exe

=====REZULTATUL PROGRAMULUI 'Exemplu_3_5_4_new.exe' 
Numarul de procese pe axa 0 este 3; Numarul de procese pe axa 1 este 3; Numarul de procese pe axa 2 este 3; 
Procesul cu rankul 0 are coordonatele (0,0,0)
Procesul cu rankul 1 are coordonatele (0,0,1)
Procesul cu rankul 2 are coordonatele (0,0,2)
Procesul cu rankul 3 are coordonatele (0,1,0)
Procesul cu rankul 4 are coordonatele (0,1,1)
Procesul cu rankul 5 are coordonatele (0,1,2)
Procesul cu rankul 6 are coordonatele (0,2,0)
Procesul cu rankul 7 are coordonatele (0,2,1)
Procesul cu rankul 8 are coordonatele (0,2,2)
Procesul cu rankul 9 are coordonatele (1,0,0)
Procesul cu rankul 10 are coordonatele (1,0,1)
Procesul cu rankul 11 are coordonatele (1,0,2)
Procesul cu rankul 12 are coordonatele (1,1,0)
Procesul cu rankul 13 are coordonatele (1,1,1)
Procesul cu rankul 14 are coordonatele (1,1,2)
Procesul cu rankul 15 are coordonatele (1,2,0)
Procesul cu rankul 16 are coordonatele (1,2,1)
Procesul cu rankul 17 are coordonatele (1,2,2)
Procesul cu rankul 18 are coordonatele (2,0,0)
Procesul cu rankul 19 are coordonatele (2,0,1)
Procesul cu rankul 20 are coordonatele (2,0,2)
Procesul cu rankul 21 are coordonatele (2,1,0)
Procesul cu rankul 22 are coordonatele (2,1,1)
Procesul cu rankul 23 are coordonatele (2,1,2)
Procesul cu rankul 24 are coordonatele (2,2,0)
Procesul cu rankul 25 are coordonatele (2,2,1)
Procesul cu rankul 26 are coordonatele (2,2,2)
Sunt procesul cu rankul 2 (0,0,2) vecinii mei sunt: 
   pe directia axei X : stanga -2(-1,-1,-1) dreapta 11(1,0,2) 
   pe directia axei Y : stanga -2(-1,-1,-1) dreapta 5(0,1,2) 
   pe directia axei Z : jos 1(0,0,1) sus -2(-1,-1,-1) 
Valorile negative semnifica lipsa procesului vecin!
[Hancu_B_S@hpc Notate_Exemple]$ 
*/
