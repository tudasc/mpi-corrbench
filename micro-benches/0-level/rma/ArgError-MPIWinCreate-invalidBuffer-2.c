#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
/*
 * invalid buffer (buffer on temporary stack mem will be freed at function exit) (line 14)
 *
 */

#define N 10

void get_win(MPI_Win *win) {
  int buffer[N];

  MPI_Win_create(buffer, N * sizeof(int), 1, MPI_INFO_NULL, MPI_COMM_WORLD, win);

  return;
}

int main(int argc, char *argv[]) {
  int rank, numProcs;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  MPI_Win win;

  get_win(&win);

  MPI_Win_free(&win);

  MPI_Finalize();

  return 0;
}
