#include <mpi.h>
#include <stddef.h>
#include <stdio.h>

#define MSG_TAG_A 124523
#define N 1000

/*
 * Send and recv type signatures do not match. line 25
 */

int main(int argc, char *argv[]) {
  int rank;
  int buffer[N] = {0};
  unsigned int ubuffer[N] = {0};

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    MPI_Send(ubuffer, N, MPI_UNSIGNED, 1, MSG_TAG_A, MPI_COMM_WORLD);
  } else if (rank == 1) {
    MPI_Request req;
    MPI_Status stat;
    MPI_Irecv(buffer, N, MPI_INT, 0, MSG_TAG_A, MPI_COMM_WORLD, &req);
    MPI_Wait(&req, &stat);
  }

  MPI_Finalize();

  return 0;
}
