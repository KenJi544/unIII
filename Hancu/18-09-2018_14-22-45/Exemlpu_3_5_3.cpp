/*
Acest program realizeaza urmatoarele:
1. se creaza un nou grup de procese care contine cite un singur proces de pe nod;
2. pentru acest grup de procese se creaza un comunicator cu topologie de tip cerc;
3. se realizeaza transmiterea de mesage "pe cerc";
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int i, p, k=0, size, size_new, rank, rank_new, sour, dest;
    int Node_rank, rank_gr;
    int Nodes; //numarul  de noduri
    int local_rank = atoi(getenv("OMPI_COMM_WORLD_LOCAL_RANK"));
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Status status;
    MPI_Comm com_new, ring1;
    MPI_Group MPI_GROUP_WORLD, newgr;

    int dims[1], period[1], reord;
    int *ranks,*newGroup;
    int namelen;
    int D1 = 123, D2;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);
    if (rank == 0)
        printf("=====REZULTATUL PROGRAMULUI '%s' \n", argv[0]);
    MPI_Barrier(MPI_COMM_WORLD);
 // Se determina numarul de noduri (care este si numarul de procese in grupul creat
    if (local_rank == 0) k = 1;
    MPI_Allreduce(&k, &Nodes, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    newGroup=(int *) malloc(Nodes * sizeof(int));
    ranks = (int *) malloc(size * sizeof(int));
     int r;
 // Se construieste vectorul newGroup   
    if (local_rank == 0)
    	ranks[rank] = rank;
    else
    	ranks[rank] = -1;
    	
    for (int i = 0; i < size; ++i)
    	MPI_Bcast(&ranks[i], 1, MPI_INT, i, MPI_COMM_WORLD);
     for (int i = 0, j = 0; i < size; ++i)
    {
    	if (ranks[i] != -1)
    	{
    		newGroup[j] = ranks[i];
    		++j;
    	}
    }
    MPI_Comm_group(MPI_COMM_WORLD, &MPI_GROUP_WORLD);
    MPI_Group_incl(MPI_GROUP_WORLD, Nodes, newGroup, &newgr);
    MPI_Comm_create(MPI_COMM_WORLD, newgr, &com_new);

    MPI_Group_rank(newgr, &rank_gr);

    if (rank_gr != MPI_UNDEFINED) {
        MPI_Comm_size(com_new, &size_new);
        MPI_Comm_rank(com_new, &rank_new);

        dims[0] = size_new; // numarul de procesoare
        period[0] = 1; //1 - daca e inchisa
        reord = 1;
      
        MPI_Barrier(com_new);

        //realizara topologiei de tip cerc
        MPI_Cart_create(com_new, 1, dims, period, reord, &ring1);
        MPI_Cart_shift(ring1, 1, 2, &sour, &dest);

        D1 = D1 + rank;
        MPI_Sendrecv(&D1, 1, MPI_INT, dest, 12, &D2, 1, MPI_INT, sour, 12, ring1, &status);

        MPI_Barrier(com_new);

        if (rank_new == 0) {
       printf("===Rezultatul MPI_Sendrecv:\n");
            MPI_Barrier(com_new);
        }
        else MPI_Barrier(com_new);
printf ("Process %d (%d from %s), received from proces %d the value %d and send to proces %d the value %d\n",rank_new,rank,processor_name,sour,D2,dest,D1);
        MPI_Barrier(com_new);
        MPI_Group_free(&newgr);
        MPI_Comm_free(&ring1);
        MPI_Comm_free(&com_new);
    }

    MPI_Finalize();
    return 0;
}
