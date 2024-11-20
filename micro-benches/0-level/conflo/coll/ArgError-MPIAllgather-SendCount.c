#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
/*
 * Wrong number of elements to send in MPI_Allgather. line 17
 *
 */
int main(int argc, char *argv[]) {
  int myRank, numProcs;
  MPI_Init(&argc, &argv);

  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

  int local_sum = 4;
  int global_sum[2] = {0};
  int num_elements = 1;

  if (argc != 1) {  // always provoke the error
    num_elements = 1;
  } else {
    num_elements = 2;
  }
  MPI_Allgather(&local_sum, num_elements, MPI_INT, global_sum, 1, MPI_INT, MPI_COMM_WORLD);

  if (myRank == 0) {
    printf("Result: %d %d\n", global_sum[0], global_sum[1]);
  }

  MPI_Finalize();

  return 0;
}
