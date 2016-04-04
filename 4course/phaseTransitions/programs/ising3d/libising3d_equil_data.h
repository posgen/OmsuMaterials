#ifndef LIBISING3D_EQUIL_DATA
#define LIBISING3D_EQUIL_DATA

#include <cstdlib>
#include <cmath>
#include "mt64.h"

namespace libising3d {

    /*
        Структура для сохранения общей конфигурации исследования:
            mc_excluded_steps   - число шагов Монте-Карло (далее - МК), отводимых на достижение термодинамического равновесия
            mc_collected_steps  - число шагов МК для накопления средних значений требуемых величин (энергия, намагниченность и др.)
            temperature         - температура окружающей среды
    */
    struct IsingConfiguration
    {
      size_t mc_collected_steps;
      size_t mc_excluded_steps;
      double temperature;
    };

    /*
        Структура для хранения исследуемой системы. В данном случае - трёхмерной кубической решётки.
            linear_size     - линейный размер системы
            spins_number    - количество спинов в исследуемой системе (в общем случае, может отличаться от linear_size^3)
            spin_structure  - указатель на трёхмерный массив целых чисел
    */
    struct Ising3DSystem
    {
      size_t linear_size, spins_number;
      int8_t ***spin_structure;
    };


    /*
        Структура для накопления энергии, намагниченности и их вторых моментов на каждом шаге МК.
        После проведелния исследования данные величины используются для вычисления средних значений (энергия/намагниченность),
        а также для расчёта теплоёмкости и магнитной восприимчивости системы.
    */
    struct Cumulant {
      long double m_cumulant, m2_cumulant, e_cumulant, e2_cumulant;
    };

    /*
        Пример расчёта релаксационного времени через экспонециальное спадание намагниченности.
        Применимо только для удельной начальной намагниченности m0 = 1 и температуры T выше критической Tc.
    */
    size_t get_relaxation_for_order_init_state(const Ising3DSystem systm, const double temperature);

    /*
        Функция для инициализации генератора псевдо случайных чисел, используемого в алгоритме Метрополиса
    */
    void set_generator_seed(const unsigned long long seed);

    /*
        Функция для проведения исследования и получения кумулятивных значений.
    */
    Cumulant run_equilibrium_research(const IsingConfiguration systm_config, const Ising3DSystem systm);
};

#endif
