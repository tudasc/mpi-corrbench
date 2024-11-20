#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
/*
 * Host language buffer types and MPI types don't agree. line 17
 *
 */
int main(int argc, char *argv[]) {
  int myRank, numProcs;

  int local_sum = 4;
  int global_sum[2] = {0};

  MPI_Init(&argc, &argv);

  int root = 0;
  MPI_Datatype recv_t = MPI_INT;
  if (argc == 1) {
    recv_t = MPI_CHAR;
  } else {
    recv_t = MPI_INT;
  }

  MPI_Gather(&local_sum, 1, recv_t, global_sum, 1, MPI_INT, root, MPI_COMM_WORLD);

  MPI_Finalize();

  return 0;
}
