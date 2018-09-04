#ifndef FFHELPERS_H_INCLUDED
#define FFHELPERS_H_INCLUDED

#include <iostream>
#include <limits>
#include <string>
#include <random>

#include <cmath>
#include <cstdlib>

namespace
{
void clear_stdin();

std::random_device hw_rnd{};
std::mt19937_64 gnr{ hw_rnd() };
}

namespace ffomsu
{

template<typename TValue>
void get_value(TValue& val, const std::string intro = "")
{
    do {
        if (intro != "") {
            std::cout << intro;
        }

        std::cin >> val;

        if ( std::cin.fail() ) {
            clear_stdin();
        } else {
            break;
        }
    } while (true);

    clear_stdin();
}

std::string get_line(const std::string intro = "", const char separator = '\n')
{
    std::string tmp;

    if (intro != "") {
        std::cout << intro;
    }

    std::getline(std::cin, tmp, separator);
    return tmp;
}

template<typename TValue>
void print(const TValue& value)
{
    std::cout << value;
}

template<typename T, typename... Targs>
void print(T value, Targs... Fargs)
{
    std::cout << value;
    print(Fargs...);
}

/// Случайное число в интервале [min; max]
size_t rand()
{
    return gnr();
}

/// Случайное число в интервале [0.0; 1.0]
double rand_0_1_incl()
{
    static constexpr auto gnr_max = double( gnr.max() );
    return gnr() / gnr_max;
}

/// Случайное число в интервале [0.0; 1.0)
double rand_0_1_excl()
{
    static constexpr double factor = 1.0 / 9007199254740992.0;
    return (gnr() >> 11) * factor;
}

/// Случайное число в интервале [a; b]
double rand_a_b_incl(const double a = 0.0, const double b = 1.0)
{
    return a + (b - a) * rand_0_1_incl();
}

/// Случайное число в интервале [a; b)
double rand_a_b_excl(const double a = 0.0, const double b = 1.0)
{
    return a + (b - a) * rand_0_1_excl();
}

size_t rand_max()
{
    return gnr.max();
}

size_t rand_min()
{
    return gnr.min();
}

void rand_re_seed()
{
    gnr.seed(hw_rnd());
}

void rand_re_seed(const size_t seed)
{
    gnr.seed(seed);
}

}

namespace
{

void clear_stdin()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

}



#endif // FFHELPERS_H_INCLUDED
