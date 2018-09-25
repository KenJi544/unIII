#include "mpi.h"
#include <stdio.h>
#include <math.h>
typedef struct
{
	float position[3];
	float mass;
} Particle;
MPI_Datatype MPI_Particle; 
	void construct_datatypes(void)
	{
	Particle p;
	int blens[2];
	MPI_Aint displ[2];
	MPI_Datatype types[2];
	blens[0]=3; types[0]=MPI_FLOAT;
	displ[0]=(MPI_Aint)&p.position-(MPI_Aint)&p;
	blens[1]=1; types[1]=MPI_FLOAT;
	displ[1]=(MPI_Aint)&p.mass-(MPI_Aint)&p;
	MPI_Type_struct(2,blens,displ,types,&MPI_Particle);
	MPI_Type_commit(&MPI_Particle);
	return;
	}
int main(int argc, char *argv[])
{
int nProc,myRank,i;
Particle *myP;
MPI_Init(&argc,&argv);          
MPI_Comm_size(MPI_COMM_WORLD,&nProc); 
MPI_Comm_rank(MPI_COMM_WORLD,&myRank); 
construct_datatypes();
if (myRank ==0)
printf("\n=====REZULTATUL PROGRAMULUI '%s' \n",argv[0]); 
MPI_Barrier(MPI_COMM_WORLD);
myP=(Particle*)calloc(nProc,sizeof(Particle));
if(myRank == 0){
for(i=0;i<nProc;i++){
myP[i].position[0]=i;myP[i].position[1]=i+1;myP[i].position[2]=i+2;
myP[i].mass=10+100.0*rand()/RAND_MAX;
		    }
	       }
MPI_Bcast(myP,nProc,MPI_Particle,0,MPI_COMM_WORLD);
printf("Proces rank %d: pozitia particuleei (%f, %f, %f) masa ei %f\n",myRank,myP[myRank].position[0],myP[myRank].position[1],myP[myRank].position[2],myP[myRank].mass);
MPI_Finalize();             
return 0; 
}
/*
[Hancu_B_S@hpc Notate_Exemple]$ /opt/openmpi/bin/mpiCC -o Exemplu_3_8_1.exe Exemplu_3_8_1.cpp
[Hancu_B_S@hpc Notate_Exemple]$ /opt/openmpi/bin/mpirun -n 16 -machinefile ~/nodes4  Exemplu_3_8_1.exe

=====REZULTATUL PROGRAMULUI 'Exemplu_3_8_1.exe' 
Proces rank 0: pozitia particuleei (0.000000, 1.000000, 2.000000) masa ei 94.018768
Proces rank 2: pozitia particuleei (2.000000, 3.000000, 4.000000) masa ei 88.309921
Proces rank 4: pozitia particuleei (4.000000, 5.000000, 6.000000) masa ei 101.164734
Proces rank 12: pozitia particuleei (12.000000, 13.000000, 14.000000) masa ei 46.478447
Proces rank 8: pozitia particuleei (8.000000, 9.000000, 10.000000) masa ei 37.777470
Proces rank 6: pozitia particuleei (6.000000, 7.000000, 8.000000) masa ei 43.522274
Proces rank 14: pozitia particuleei (14.000000, 15.000000, 16.000000) masa ei 105.222969
Proces rank 10: pozitia particuleei (10.000000, 11.000000, 12.000000) masa ei 57.739704
Proces rank 1: pozitia particuleei (1.000000, 2.000000, 3.000000) masa ei 49.438293
Proces rank 3: pozitia particuleei (3.000000, 4.000000, 5.000000) masa ei 89.844002
Proces rank 5: pozitia particuleei (5.000000, 6.000000, 7.000000) masa ei 29.755136
Proces rank 15: pozitia particuleei (15.000000, 16.000000, 17.000000) masa ei 101.619507
Proces rank 11: pozitia particuleei (11.000000, 12.000000, 13.000000) masa ei 72.887093
Proces rank 7: pozitia particuleei (7.000000, 8.000000, 9.000000) masa ei 86.822960
Proces rank 13: pozitia particuleei (13.000000, 14.000000, 15.000000) masa ei 61.340092
Proces rank 9: pozitia particuleei (9.000000, 10.000000, 11.000000) masa ei 65.396996
[Hancu_B_S@hpc Notate_Exemple]$ 

*/
