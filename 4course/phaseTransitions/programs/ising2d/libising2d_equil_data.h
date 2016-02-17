#ifndef LIBISING2D_EQUIL_DATA
#define LIBISING2D_EQUIL_DATA

#include <math.h>
#include "mt64.h"

typedef struct Ising2DCfn
{
  unsigned int mc_collected_steps;
  unsigned int mc_excluded_steps;
  double temperature;
} Ising2DConfiguration;

typedef struct Ising2DStm
{
  unsigned int linear_size, spins_number;
  int **spin_structure;
} Ising2DSystem;

typedef struct CumValue {
  long double m_cumulant, m2_cumulant, e_cumulant, e2_cumulant;
} Cumulant;

unsigned int get_relaxation_time(const Ising2DSystem, const double, const unsigned long long);
Cumulant run_equilibrium_research(const Ising2DConfiguration, const Ising2DSystem, const unsigned long long);

#endif
