#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "libising2d_equil_data.h"

int** allocate_array2D(unsigned int size)
{
  unsigned int i = 0;
  int **arr;

  arr = (int **) calloc(size, sizeof(int **));
  for (; i < size; i++)
    arr[i] = (int *) calloc(size, sizeof(int *));

  return arr;
}

void free_array2D(int ***arr, unsigned int size)
{
  int i = 0;

  for (; i < size; i++)
    free( (*arr)[i] );

  free(*arr);
}

int main()
{
    unsigned int lin_size, rel_time;
    int **spin_array, i, j;

    Ising2DSystem systm;

    printf("Enter linear size of system: ");
    scanf("%d", &lin_size);

    spin_array = allocate_array2D(lin_size);
    for (i = 0; i < lin_size; i++) {
        for (j = 0; j < lin_size; j++) {
            spin_array[i][j] = 1;
        }
    }

    systm.linear_size = lin_size;
    systm.spins_number = lin_size * lin_size;
    systm.spin_structure = spin_array;

    rel_time = get_relaxation_time(systm, 3.5, time(NULL));
    printf("The relaxation time is: %d", rel_time);

    free_array2D(&spin_array, lin_size);
    return 0;
}
