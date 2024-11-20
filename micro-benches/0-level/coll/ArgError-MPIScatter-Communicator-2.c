#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
/*
 * Commnunicator is null pointer. (line 16)
 */
int main(int argc, char *argv[]) {
  int myRank, numProcs;

  int local_sum[2] = {1, 1};
  int global_sum = 0;

  MPI_Init(&argc, &argv);

  int root = 0;

  MPI_Comm comm = NULL;
  MPI_Scatter(local_sum, 1, MPI_DOUBLE, &global_sum, 1, MPI_INT, root, comm);

  MPI_Finalize();

  return 0;
}
