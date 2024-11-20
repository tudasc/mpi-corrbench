#include <mpi.h>
#include <stddef.h>
#include <stdlib.h>

#define MY_TAG 0

/*
 * Type error in Send/Receive: signedness of integer not respected.
 * line 23, 27, 29
 */

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int my_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  unsigned int *buf = (unsigned int *)malloc(4 * sizeof(unsigned int));
  buf[0] = buf[1] = buf[2] = buf[3] = 1;

  MPI_Datatype two_ints;
  MPI_Type_contiguous(4, MPI_INT, &two_ints);
  MPI_Type_commit(&two_ints);

  if (my_rank == 0) {
    MPI_Send(buf, 1, two_ints, 1, MY_TAG, MPI_COMM_WORLD);
  } else if (my_rank == 1) {
    MPI_Recv(buf, 1, two_ints, 0, MY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  MPI_Type_free(&two_ints);
  MPI_Finalize();

  free(buf);

  return 0;
}
