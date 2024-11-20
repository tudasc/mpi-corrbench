#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MY_TAG 0

/*
 * Type mismatch between MPI_Send and MPI_Recv
 * Rank 1 locally commits a vector type with different block length.
 * line 39
 */

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int my_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  /* buf is matrix with x*y elements [x][y] */
  const int x = 16;
  const int y = 16;
  const int m_size = x * y;
  float *buf = (float *)malloc(m_size * sizeof(float));

  for (int i = 0; i < m_size; ++i) {
    buf[i] = i;
  }

  MPI_Datatype col_t;
  /* One column vector */
  MPI_Type_vector(16, 1, 16, MPI_FLOAT, &col_t);
  MPI_Type_commit(&col_t);

  if (my_rank == 0) {
    MPI_Send(buf, 1, col_t, 1, MY_TAG, MPI_COMM_WORLD);
  } else if (my_rank == 1) {
    MPI_Type_free(&col_t);
    MPI_Type_vector(16, 2, 16, MPI_FLOAT, &col_t);
    MPI_Type_commit(&col_t);
    MPI_Recv(buf, 1, col_t, 0, MY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  MPI_Type_free(&col_t);
  MPI_Finalize();

  free(buf);

  return 0;
}
