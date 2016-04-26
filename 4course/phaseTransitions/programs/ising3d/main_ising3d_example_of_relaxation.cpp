#include <iostream>
#include <ctime>

#include "libising3d_equil_data.h"

using namespace std;
using namespace libising3d;

int8_t*** allocate_array3D(size_t size)
{
    int8_t ***arr;

    arr = new int8_t**[size];
    for (size_t i = 0; i < size; ++i) {
        arr[i] = new int8_t*[size];

        for (size_t j = 0; j < size; ++j) {
            arr[i][j] = new int8_t[size];
        }
    }

    return arr;
}

void delete_array3D(int8_t ****arr, unsigned int size)
{
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            delete[] (*arr)[i][j];
        }

        delete[] (*arr)[i];
    }

    delete[] *arr;
}

int main()
{
    size_t lin_size, rel_time, i, j, k;
    int8_t ***spin_array;

    Ising3DSystem systm;
    IsingConfiguration cfg;

    cout << "Enter linear size of system: ";
    cin >> lin_size;

    spin_array = allocate_array3D(lin_size);

    systm.linear_size = lin_size;
    systm.spins_number = lin_size * lin_size * lin_size;
    systm.spin_structure = spin_array;

    set_generator_seed( (unsigned long long) time(NULL));

    for (double temp = 5.5; temp > 4.6; temp -= 0.1) {
        for (i = 0; i < lin_size; ++i) {
            for (j = 0; j < lin_size; ++j) {
                for (k = 0; k < lin_size; ++k) {
                    systm.spin_structure[i][j][k] = 1;
                }
            }
        }

        cfg.temperature = temp;
        rel_time = get_relaxation_for_order_init_state(cfg, systm);
        cout << "For temperature " << temp << " the relaxation time is: " << rel_time << endl;
    }

    delete_array3D(&spin_array, lin_size);
    return 0;
}
