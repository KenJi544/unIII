#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
int main(int argc, char *argv[]) 
{
int i, p, k=0, size, rank, rank_new;
int Node_rank;
int Nodes; //numarul  de noduri
int local_rank = atoi(getenv("OMPI_COMM_WORLD_LOCAL_RANK"));
char processor_name[MPI_MAX_PROCESSOR_NAME];
MPI_Status status;
MPI_Comm com_new, ring1;
MPI_Group MPI_GROUP_WORLD, newgr;
int *ranks,*newGroup;
int namelen;
MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Get_processor_name(processor_name, &namelen);
if (rank == 0) {
printf("=====REZULTATUL PROGRAMULUI '%s' \n", argv[0]);
printf ("Rankurile proceselor din comunicatorului 'MPI_COMM_WOLD' au fost repartizate astfel: \n"); }
MPI_Barrier(MPI_COMM_WORLD);
 // Se determina numarul de noduri (care este si numarul de procese in grupul creat
printf ("Rankul %d de pe nodul %s. \n",rank,processor_name); 
if (local_rank == 0) k = 1;
MPI_Allreduce(&k, &Nodes, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
newGroup=(int *)malloc(Nodes*sizeof(int));
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
MPI_Group_rank(newgr, &rank_new);
if (rank_new!= MPI_UNDEFINED)
printf ("Procesul cu rankul %d al comunicatorului 'com_new'(%d com. 'MPI_COMM_WOLD') de pe nodul %s. \n", rank_new,rank,processor_name);
MPI_Finalize();
return 0;
}
