#include "libising2d_equil_data.h"

#define PROBABILITIES_SIZE 5

namespace libising2d {

    void prepare_research(double *, const double, const Ising2DSystem, int &, int &);
    void do_step(int **spins, const double *, const size_t, const size_t, int &, int &);

    size_t next_spin(const size_t, const size_t);
    size_t prev_spin(const size_t, const size_t);

    /***************** Public functions ***********************/

    Cumulant run_equilibrium_research(const Ising2DConfiguration cfg, const Ising2DSystem systm)
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

        results.m_cumulant += (long double) magn;
        results.m2_cumulant += (long double) magn * magn;
        results.e_cumulant += (long double) energy;
        results.e2_cumulant += (long double) energy * energy;
      }

      return results;
    }

    unsigned int get_relaxation_time(Ising2DSystem systm, const double temperature)
    {
      unsigned int mc_counter = 0, equil_attempts = 0;
      int magn = 0, energy = 0;
      double w_array[PROBABILITIES_SIZE], precision = 0.000001, cur_unit_magn, prev_unit_magn = 0.0;

      prepare_research(w_array, temperature, systm, energy, magn);
      cur_unit_magn = (double) magn / systm.spins_number;

      while ( equil_attempts != 5 ) {
        do_step(systm.spin_structure, w_array, systm.linear_size, systm.spins_number, energy, magn);
        prev_unit_magn = cur_unit_magn;
        cur_unit_magn = (double) magn / systm.spins_number;
        mc_counter++;

        if ( fabs(cur_unit_magn - prev_unit_magn) <= precision )
            equil_attempts++;
      }

      return mc_counter;
    }

    void set_generator_seed(const unsigned long long rng_seed)
    {
        init_genrand64(rng_seed);
    }

    /***************** Private functions ***********************/
    void prepare_research(double *w_array, const double temp, const Ising2DSystem systm, int &current_energy, int &current_magn)
    {
      size_t i, j, linear_size = systm.linear_size;
      int neibours_sum;
      int **spins = systm.spin_structure;

      // Prepare all possible probabilities array
      w_array[0] = 1;
      for (i = 1; i < PROBABILITIES_SIZE; i++) {
        w_array[i] = std::exp( (-2.0 * i) / temp);
      }

      // Calculate initial energy and magnetization
      for (i = 0; i < systm.linear_size; i++) {
        for (j = 0; j < systm.linear_size; j++) {
          neibours_sum = spins[next_spin(i, linear_size)][j] + spins[prev_spin(i, linear_size)][j] + spins[i][next_spin(j, linear_size)] + spins[i][prev_spin(j, linear_size)];
          current_magn += spins[i][j];
          current_energy += -1 * spins[i][j] * neibours_sum;
        }
      }
    }

    inline void do_step(int **spins, const double *w_array, const size_t linear_size, const size_t spins_number, int &current_energy, int &current_magn)
    {
      int neibours_sum, diff_energy;
      size_t counter = 1, i, j;

      do {
        i = (size_t)(linear_size * genrand64_real2());
        j = (size_t)(linear_size * genrand64_real2());

        if ( spins[i][j] == 0 )
          continue;

        neibours_sum = spins[next_spin(i, linear_size)][j] + spins[prev_spin(i, linear_size)][j] + spins[i][next_spin(j, linear_size)] + spins[i][prev_spin(j, linear_size)];
        diff_energy = neibours_sum * spins[i][j];

        if ( (diff_energy <= 0) || (genrand64_real1() < w_array[diff_energy]) ) {
          spins[i][j] = -spins[i][j];

          current_magn    += 2 * spins[i][j];
          current_energy  += 2 * diff_energy;
        }
      } while ( ++counter != spins_number);
    }

    size_t next_spin(const size_t position, const size_t linear_size)
    {
      if ( position == (linear_size - 1) )
        return 0;
      else
        return position + 1;
    }

    size_t prev_spin(const size_t position, const size_t linear_size)
    {
      if ( position == 0 )
        return linear_size - 1;
      else
        return position - 1;
    }

};
