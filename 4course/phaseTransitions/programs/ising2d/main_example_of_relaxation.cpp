#include <iostream>
#include <ctime>

#include "libising2d_equil_data.h"

using namespace std;
using namespace libising2d;

int** allocate_array2D(unsigned int size)
{
  unsigned int i = 0;
  int **arr;

  arr = new int*[size];
  for (; i < size; i++)
    arr[i] = new int[size];

  return arr;
}

void free_array2D(int ***arr, unsigned int size)
{
  for (unsigned int i = 0; i < size; i++)
    delete[] (*arr)[i];

  delete[] *arr;
}

int main()
{
    unsigned int lin_size, rel_time, i, j;
    int **spin_array;

    Ising2DSystem systm;

    cout << "Enter linear size of system: ";
    cin >> lin_size;

    spin_array = allocate_array2D(lin_size);
    for (i = 0; i < lin_size; i++) {
        for (j = 0; j < lin_size; j++) {
            spin_array[i][j] = 1;
        }
    }

    systm.linear_size = lin_size;
    systm.spins_number = lin_size * lin_size;
    systm.spin_structure = spin_array;

    set_generator_seed( (unsigned long long) time(NULL));
    rel_time = get_relaxation_time(systm, 3.5);
    cout << "The relaxation time is: " << rel_time << endl;

    free_array2D(&spin_array, lin_size);

    return 0;
}