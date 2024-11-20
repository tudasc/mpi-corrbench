#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
/*
 * MPI type does not match host send buffer. (line 16)
 */
int main(int argc, char *argv[]) {
  int myRank, numProcs;

  int local_sum[2] = {1, 1};
  unsigned int global_sum = 0;

  MPI_Init(&argc, &argv);

  int root = 0;

  MPI_Scatter(local_sum, 1, MPI_UNSIGNED, &global_sum, 1, MPI_UNSIGNED, root, MPI_COMM_WORLD);

  MPI_Finalize();

  return 0;
}
