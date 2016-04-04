#include "libising3d_equil_data.h"

#define PROBABILITIES_SIZE 7

namespace libising3d {

    void prepare_research(double *, const double, const Ising3DSystem, int &, int &);
    void do_step(int8_t ***spins, const double *, const size_t, const size_t, int &, int &);

    size_t next_spin(const size_t, const size_t);
    size_t prev_spin(const size_t, const size_t);

    /***************** Public functions ***********************/

    Cumulant run_equilibrium_research(const IsingConfiguration cfg, const Ising3DSystem systm)
    {
      int magn = 0, energy = 0;

      double w_array[PROBABILITIES_SIZE];
      Cumulant results = { 0.0, 0.0, 0.0, 0.0 };

      prepare_research(w_array, cfg.temperature, systm, energy, magn);

      for (size_t eqil_counter = 0; eqil_counter < cfg.mc_excluded_steps; eqil_counter++) {
        do_step(systm.spin_structure, w_array, systm.linear_size, systm.spins_number, energy, magn);
      }

      for (size_t mc_counter = 0; mc_counter < cfg.mc_collected_steps; mc_counter++) {
        do_step(systm.spin_structure, w_array, systm.linear_size, systm.spins_number, energy, magn);

        results.m_cumulant  += static_cast<long double>( magn );
        results.m2_cumulant += ( static_cast<long double>( magn ) * magn ) / systm.spins_number;
        results.e_cumulant  += static_cast<long double>( energy );
        results.e2_cumulant += ( static_cast<long double>( energy ) * energy ) / systm.spins_number;
      }

      return results;
    }


    /*
        Вычисление времени релаксации по спаданию намагниченности системы в e^2 раз.
        Подходит только для начального состояния с соноправленными спинами. e^2 -
        используется для получения более явной последовательности при разных температурах.

        Если в начальной конфигурации системы все спины не соноправлены, то возращается 0.
    */
    size_t get_relaxation_for_order_init_state(Ising3DSystem systm, const double temperature)
    {
        size_t mc_counter = 0;
        int magn = 0, energy = 0;
        double w_array[PROBABILITIES_SIZE], cur_unit_magn, init_unit_magn;

        prepare_research(w_array, temperature, systm, energy, magn);

        if ( magn != int( systm.spins_number ) ) {
            return 0;
        }

        init_unit_magn = cur_unit_magn = (double) magn / systm.spins_number;

        while ( true ) {
            do_step(systm.spin_structure, w_array, systm.linear_size, systm.spins_number, energy, magn);
            cur_unit_magn = (double) magn / systm.spins_number;
            ++mc_counter;

            if ( init_unit_magn / cur_unit_magn >= std::exp(2.0) ) {
                break;
            }

            if ( mc_counter > 10000 ) {
                break;
            }
        }

        return mc_counter;
    }

    void set_generator_seed(const unsigned long long rng_seed)
    {
        init_genrand64(rng_seed);
    }

    /***************** Private functions ***********************/
    void prepare_research(double *w_array, const double temp, const Ising3DSystem systm, int &current_energy, int &current_magn)
    {
        size_t i, j, k, linear_size = systm.linear_size;
        int neibours_sum;
        int8_t ***spins = systm.spin_structure;

        // Prepare all possible probabilities array
        w_array[0] = 1;
        for (i = 1; i < PROBABILITIES_SIZE; i++) {
            w_array[i] = std::exp( (-2.0 * i) / temp);
        }

        // Calculate initial energy and magnetization
        for (i = 0; i < linear_size; ++i) {
            for (j = 0; j < linear_size; ++j) {
                for (k = 0; k < linear_size; ++k) {
                    neibours_sum = spins[next_spin(i, linear_size)][j][k] + spins[prev_spin(i, linear_size)][j][k]
                                    + spins[i][next_spin(j, linear_size)][k] + spins[i][prev_spin(j, linear_size)][k]
                                    + spins[i][j][next_spin(k, linear_size)] + spins[i][j][prev_spin(k, linear_size)];

                    current_magn    += spins[i][j][k];
                    current_energy  -= spins[i][j][k] * neibours_sum;
                }
            }
        }
    }

    inline void do_step(int8_t ***spins, const double *w_array, const size_t linear_size, const size_t spins_number, int &current_energy, int &current_magn)
    {
        int neibours_sum, diff_energy;
        size_t counter = 1, i, j, k;

        do {
            i = size_t( linear_size * genrand64_real2() );
            j = size_t( linear_size * genrand64_real2() );
            k = size_t( linear_size * genrand64_real2() );

            if ( spins[i][j][k] == 0 ) {
              continue;
            }

            neibours_sum = spins[next_spin(i, linear_size)][j][k] + spins[prev_spin(i, linear_size)][j][k]
                                    + spins[i][next_spin(j, linear_size)][k] + spins[i][prev_spin(j, linear_size)][k]
                                    + spins[i][j][next_spin(k, linear_size)] + spins[i][j][prev_spin(k, linear_size)];
            diff_energy = neibours_sum * spins[i][j][k];

            if ( (diff_energy <= 0) || (genrand64_real1() < w_array[diff_energy]) ) {
              spins[i][j][k] = -spins[i][j][k];

              current_magn    += 2 * spins[i][j][k];
              current_energy  += 2 * diff_energy;
            }
        } while ( ++counter != spins_number);
    }

    size_t next_spin(const size_t position, const size_t linear_size)
    {
        if ( position == (linear_size - 1) ) {
            return 0;
        } else {
            return position + 1;
        }
    }

    size_t prev_spin(const size_t position, const size_t linear_size)
    {
        if ( position == 0 ) {
            return linear_size - 1;
        } else {
            return position - 1;
        }
    }

};
