/* In acest program:
1) se creaza un comunicator cu topologie carteziana de tip paralelepiped;
2) se fixeaza o fateta a paralepipedului si se determina vecinii pentru procesele care apartin muchiilor
   acestei fatete (in directia miscarii acelor de ceas pe planul fatetei).
*/
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
int left_y,right_y,right_x,left_x,up_z, down_z;
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
printf("\n===== REZULTATUL PROGRAMULUI '%s' \n",argv[0]); 	 	
for ( int i = 0; i < 3; i++ )
{
cout << "Numarul de procese pe axa "<< i<< " este "<< dims[i] << "; ";
cout << endl;
}	
cout << "===Rankul si coordonatele proceselor de pe fateta laterala a paralelepipedului pentru x= " << dims[0]-1 << " ";
cout << endl; 
}
MPI_Barrier(MPI_COMM_WORLD);
MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, reorder, &comm);
MPI_Cart_coords(comm, rank, ndims, coords);  
sleep(rank); 

if(coords[0] == dims[0]-1)
cout << "Procesul cu rankul " << rank << " are coordonatele (" << coords[0] << "," << coords[1] << "," << coords[2] <<")"<< endl;   
MPI_Barrier(MPI_COMM_WORLD);
if(rank == 0)
{
cout << "===Vecinii proceselor de pe muchiile fatetei laterali a paralelepipedului pentru x= "<< dims[0]-1 << " ";
cout << endl;
}
sleep(rank);
if(coords[0] == dims[0]-1)
{
if (!(((0<coords[1])&&(0<coords[2]))&&((coords[1]<dims[1]-1)&&(coords[2]<dims[2]-1))))
{
printf("Sunt procesul cu rankul %d (%d,%d,%d) vecinii mei sunt: \n",rank,coords[0],coords[1],coords[2]);
/*
MPI_Cart_shift(comm,0,1,&left_x,&right_x);
if (left_x<0) {coords_left_x[0]=-1; coords_left_x[1]=-1;coords_left_x[2]=-1;}
else {MPI_Cart_coords(comm, left_x, ndims, coords_left_x); }
if (right_x<0) {coords_right_x[0]=-1;coords_right_x[1]=-1;coords_right_x[2]=-1;}
else {MPI_Cart_coords(comm, right_x, ndims, coords_right_x); }
printf("   pe directia axei X : stanga %d(%d,%d,%d) dreapta %d(%d,%d,%d) \n",left_x,coords_left_x[0],coords_left_x[1],coords_left_x[2],right_x,coords_right_x[0],coords_right_x[1],coords_right_x[2]);
*/
if (coords[2]=0)
MPI_Cart_shift(comm,1,1,&left_y,&right_y);
if (coords[2]=dims[2]-1)
MPI_Cart_shift(comm,1,-1,&left_y,&right_y);
if (left_y<0) {coords_left_y[0]=-1; coords_left_y[1]=-1;coords_left_y[2]=-1;}
else {MPI_Cart_coords(comm, left_y, ndims, coords_left_y); }
if (right_y<0) {coords_right_y[0]=-1;coords_right_y[1]=-1;coords_right_y[2]=-1;}
else {MPI_Cart_coords(comm, right_y, ndims, coords_right_y); }
printf("   pe directia axei Y : stanga %d(%d,%d,%d) dreapta %d(%d,%d,%d) \n",left_y,coords_left_y[0],coords_left_y[1],coords_left_y[2],right_y,coords_right_y[0],coords_right_y[1],coords_right_y[2]);
 if (coords[1]=0)  
 MPI_Cart_shift(comm,2,-1,&up_z,&down_z);
if (coords[1]=dims[1]-1)  
 MPI_Cart_shift(comm,2,1,&up_z,&down_z);
 if (up_z<0) {coords_up_z[0]=-1; coords_up_z[1]=-1;coords_up_z[2]=-1;}
else {MPI_Cart_coords(comm, up_z, ndims, coords_up_z); }
if (down_z<0) {coords_down_z[0]=-1;coords_down_z[1]=-1;coords_down_z[2]=-1;}
else {MPI_Cart_coords(comm, down_z, ndims, coords_down_z); }
printf("   pe directia axei Z : jos %d(%d,%d,%d) sus %d(%d,%d,%d) \n",up_z,coords_up_z[0],coords_up_z[1],coords_up_z[2],down_z,coords_down_z[0],coords_down_z[1],coords_down_z[2]);   
}
}
MPI_Barrier(MPI_COMM_WORLD);
if(rank == 0)
printf("===Valorile negative semnifica lipsa procesului vecin!\n");
MPI_Finalize();
return 0;
}
/*
[Hancu_B_S@hpc Notate_Exemple]$ /opt/openmpi/bin/mpiCC -o Exemplu_3_5_4a.exe Exemplu_3_5_4a.cpp
[Hancu_B_S@hpc Notate_Exemple]$ /opt/openmpi/bin/mpirun -n 6  -machinefile ~/nodes6 Exemplu_3_5_4a.exe
===== REZULTATUL PROGRAMULUI 'Exemplu_3_5_4a.exe' 
Numarul de procese pe axa 0 este 3; 
Numarul de procese pe axa 1 este 2; 
Numarul de procese pe axa 2 este 1; 
===Rankul si coordonatele proceselor de pe fateta laterala a paralelepipedului pentru x= 2 
Procesul cu rankul 4 are coordonatele (2,0,0)
===Vecinii proceselor de pe muchiile fatetei laterali a paralelepipedului pentru x= 2 
Procesul cu rankul 5 are coordonatele (2,1,0)
Sunt procesul cu rankul 4 (2,0,0) vecinii mei sunt: 
   pe directia axei Y : stanga 0(0,0,0) dreapta 0(0,0,0) 
   pe directia axei Z : jos -2(-1,-1,-1) sus -2(-1,-1,-1) 
Sunt procesul cu rankul 5 (2,1,0) vecinii mei sunt: 
   pe directia axei Y : stanga 0(0,0,0) dreapta 0(0,0,0) 
   pe directia axei Z : jos -2(-1,-1,-1) sus -2(-1,-1,-1) 
===Valorile negative semnifica lipsa procesului vecin!

[Hancu_B_S@hpc Notate_Exemple]$ /opt/openmpi/bin/mpirun -n 8  -machinefile ~/nodes6 Exemplu_3_5_4a.exe
===== REZULTATUL PROGRAMULUI 'Exemplu_3_5_4a.exe' 
Numarul de procese pe axa 0 este 2; 
Numarul de procese pe axa 1 este 2; 
Numarul de procese pe axa 2 este 2; 
===Rankul si coordonatele proceselor de pe fateta laterala a paralelepipedului pentru x= 1 
Procesul cu rankul 4 are coordonatele (1,0,0)
Procesul cu rankul 5 are coordonatele (1,0,1)
Procesul cu rankul 6 are coordonatele (1,1,0)
Procesul cu rankul 7 are coordonatele (1,1,1)
===Vecinii proceselor de pe muchiile fatetei laterali a paralelepipedului pentru x= 1 
Sunt procesul cu rankul 4 (1,0,0) vecinii mei sunt: 
   pe directia axei Y : stanga 6(1,1,0) dreapta -2(-1,-1,-1) 
   pe directia axei Z : jos -2(-1,-1,-1) sus 5(1,0,1) 
Sunt procesul cu rankul 5 (1,0,1) vecinii mei sunt: 
   pe directia axei Y : stanga 7(1,1,1) dreapta -2(-1,-1,-1) 
   pe directia axei Z : jos 4(1,0,0) sus -2(-1,-1,-1) 
Sunt procesul cu rankul 6 (1,1,0) vecinii mei sunt: 
   pe directia axei Y : stanga -2(-1,-1,-1) dreapta 4(1,0,0) 
   pe directia axei Z : jos -2(-1,-1,-1) sus 7(1,1,1) 
Sunt procesul cu rankul 7 (1,1,1) vecinii mei sunt: 
   pe directia axei Y : stanga -2(-1,-1,-1) dreapta 5(1,0,1) 
   pe directia axei Z : jos 6(1,1,0) sus -2(-1,-1,-1) 
===Valorile negative semnifica lipsa procesului vecin!

[Hancu_B_S@hpc Notate_Exemple]$ /opt/openmpi/bin/mpirun -n 27  -machinefile ~/nodes6 Exemplu_3_5_4a.exe
===== REZULTATUL PROGRAMULUI 'Exemplu_3_5_4a.exe' 
Numarul de procese pe axa 0 este 3; 
Numarul de procese pe axa 1 este 3; 
Numarul de procese pe axa 2 este 3; 
===Rankul si coordonatele proceselor de pe fateta laterala a paralelepipedului pentru x= 2 
Procesul cu rankul 18 are coordonatele (2,0,0)
Procesul cu rankul 19 are coordonatele (2,0,1)
Procesul cu rankul 20 are coordonatele (2,0,2)
Procesul cu rankul 21 are coordonatele (2,1,0)
Procesul cu rankul 22 are coordonatele (2,1,1)
Procesul cu rankul 23 are coordonatele (2,1,2)
Procesul cu rankul 24 are coordonatele (2,2,0)
Procesul cu rankul 25 are coordonatele (2,2,1)
Procesul cu rankul 26 are coordonatele (2,2,2)
===Vecinii proceselor de pe muchiile fatetei laterali a paralelepipedului pentru x= 2 
Sunt procesul cu rankul 18 (2,0,0) vecinii mei sunt: 
   pe directia axei Y : stanga 21(2,1,0) dreapta -2(-1,-1,-1) 
   pe directia axei Z : jos -2(-1,-1,-1) sus 19(2,0,1) 
Sunt procesul cu rankul 19 (2,0,1) vecinii mei sunt: 
   pe directia axei Y : stanga 22(2,1,1) dreapta -2(-1,-1,-1) 
   pe directia axei Z : jos 18(2,0,0) sus 20(2,0,2) 
Sunt procesul cu rankul 20 (2,0,2) vecinii mei sunt: 
   pe directia axei Y : stanga 23(2,1,2) dreapta -2(-1,-1,-1) 
   pe directia axei Z : jos 19(2,0,1) sus -2(-1,-1,-1) 
Sunt procesul cu rankul 21 (2,1,0) vecinii mei sunt: 
   pe directia axei Y : stanga 24(2,2,0) dreapta 18(2,0,0) 
   pe directia axei Z : jos -2(-1,-1,-1) sus 22(2,1,1) 
Sunt procesul cu rankul 23 (2,1,2) vecinii mei sunt: 
   pe directia axei Y : stanga 26(2,2,2) dreapta 20(2,0,2) 
   pe directia axei Z : jos 22(2,1,1) sus -2(-1,-1,-1) 
Sunt procesul cu rankul 24 (2,2,0) vecinii mei sunt: 
   pe directia axei Y : stanga -2(-1,-1,-1) dreapta 21(2,1,0) 
   pe directia axei Z : jos -2(-1,-1,-1) sus 25(2,2,1) 
Sunt procesul cu rankul 25 (2,2,1) vecinii mei sunt: 
   pe directia axei Y : stanga -2(-1,-1,-1) dreapta 22(2,1,1) 
   pe directia axei Z : jos 24(2,2,0) sus 26(2,2,2) 
Sunt procesul cu rankul 26 (2,2,2) vecinii mei sunt: 
   pe directia axei Y : stanga -2(-1,-1,-1) dreapta 23(2,1,2) 
   pe directia axei Z : jos 25(2,2,1) sus -2(-1,-1,-1) 
===Valorile negative semnifica lipsa procesului vecin!
[Hancu_B_S@hpc Notate_Exemple]$ 
*/
