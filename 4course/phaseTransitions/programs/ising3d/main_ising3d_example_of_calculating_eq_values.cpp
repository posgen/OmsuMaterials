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

void set_low_temperature_initial_state(int8_t ***arr, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            for (size_t k = 0; k < size; ++k) {
                arr[i][j][k] = 1;
            }
        }
    }
}

int main()
{
    size_t lin_size;
    int8_t ***spin_array;

    Ising3DSystem systm;
    IsingConfiguration config;

    cout << "Enter linear size of system: ";
    cin >> lin_size;

    cout << "Enter MC steps for equilibrium: ";
    cin >> config.mc_excluded_steps;

    cout << "Enter MC steps for collecting data: ";
    cin >> config.mc_collected_steps;

    spin_array = allocate_array3D(lin_size);
    set_low_temperature_initial_state(spin_array, lin_size);

    systm.linear_size = lin_size;
    systm.spins_number = lin_size * lin_size * lin_size;
    systm.spin_structure = spin_array;

    set_generator_seed( (unsigned long long) time(NULL));

    Cumulant cum_values;
    // нормировка средних значений на один спин и количество MC шагов на сбор величин
    long double normz_coeff = 1.0 / static_cast<long double>( config.mc_collected_steps * systm.spins_number );
    long double av_magn, av_magn2, av_e, av_e2, xi, ct;


    cout << "T \t L \t m(T) \t X(T) \t e(T) \t C(T)" << endl;
    for (config.temperature = 5.5; config.temperature > 3.5; config.temperature -= 0.1) {
        cum_values = run_equilibrium_research(config, systm);

        av_magn  = cum_values.m_cumulant * normz_coeff;
        av_magn2 = cum_values.m2_cumulant / config.mc_collected_steps;
        av_e     = cum_values.e_cumulant * normz_coeff;
        av_e2    = cum_values.e2_cumulant / config.mc_collected_steps;

        xi = (av_magn2 - systm.spins_number * av_magn * av_magn) / (config.temperature);
        ct = (av_e2 - systm.spins_number * av_e * av_e) / ( config.temperature * config.temperature );

        cout << config.temperature << '\t' << systm.linear_size << '\t' << av_magn
             << '\t' << xi << '\t' << av_e << '\t' << ct << endl;
    }

    delete_array3D(&spin_array, lin_size);
    return 0;
}
