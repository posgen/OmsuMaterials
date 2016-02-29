#include <iostream>
#include <ctime>

#include "libising2d_equil_data.h"

using namespace std;
using namespace libising2d;

int** allocate_array2D(size_t size)
{
  size_t i = 0;
  int **arr;

  arr = new int*[size];
  for (; i < size; i++)
    arr[i] = new int[size];

  return arr;
}

void free_array2D(int ***arr, size_t size)
{
  for (size_t i = 0; i < size; i++)
    delete[] (*arr)[i];

  delete[] *arr;
}

void set_low_temperature_initial_state(int **arr, size_t size)
{
    size_t i = 0, j = 0;
    for (; i < size; i++) {
        for (; j < size; j++) {
            arr[i][j] = 1;
        }
    }
}

int main()
{
    size_t lin_size;
    int **spin_array;

    Ising2DSystem systm;
    Ising2DConfiguration config;

    cout << "Enter linear size of system: ";
    cin >> lin_size;

    cout << "Enter MC steps for equilibrium: ";
    cin >> config.mc_excluded_steps;

    cout << "Enter MC steps for collecting data: ";
    cin >> config.mc_collected_steps;

    spin_array = allocate_array2D(lin_size);
    set_low_temperature_initial_state(spin_array, lin_size);

    systm.linear_size = lin_size;
    systm.spins_number = lin_size * lin_size;
    systm.spin_structure = spin_array;

    set_generator_seed( (unsigned long long) time(NULL));

    Cumulant cum_values;
    // нормировка средних значений на один спин и количество MC шагов на сбор величин
    long double normz_coeff = 1.0 / (config.mc_collected_steps * systm.spins_number);
    long double av_magn, av_magn2, av_e, av_e2, xi, ct;


    cout << "T \t L \t m(T) \t X(T) \t e(T) \t C(T)" << endl;
    for (config.temperature = 3.0; config.temperature > 0.1; config.temperature -= 0.1) {
        cum_values = run_equilibrium_research(config, systm);

        av_magn  = cum_values.m_cumulant * normz_coeff;
        av_magn2 = cum_values.m2_cumulant * normz_coeff;
        av_e     = cum_values.e_cumulant * normz_coeff;
        av_e2    = cum_values.e2_cumulant * normz_coeff;

        xi = (av_magn2 - systm.spins_number * av_magn * av_magn) / (config.temperature);
        ct = (av_e2 - systm.spins_number * av_e * av_e) / ( config.temperature * config.temperature );

        cout << config.temperature << '\t' << systm.linear_size << '\t' << av_magn
             << '\t' << xi << '\t' << av_e << '\t' << ct << endl;
    }

    free_array2D(&spin_array, lin_size);

    return 0;
}