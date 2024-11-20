#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
/*
 * MPI communicator for Allgather is MPI_NULL_COMM. line 17
 *
 */
int main(int argc, char *argv[]) {
  int myRank, numProcs;

  int local_sum = 4;
  int global_sum[4];

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

  MPI_Comm null_comm = MPI_COMM_NULL;
  MPI_Allgather(&local_sum, 1, MPI_INT, global_sum, 1, MPI_INT, null_comm);

  if (myRank == 0) {
    printf("Result: %d", global_sum[0]);
  }

  MPI_Finalize();

  return 0;
}
