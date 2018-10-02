#ifndef FFHELPERS_H_INCLUDED
#define FFHELPERS_H_INCLUDED

#include <iostream>
#include <limits>
#include <string>
#include <random>

#include <cmath>
#include <cstdlib>
#include <clocale>

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

namespace
{
void clear_stdin();

std::random_device hw_rnd{};
std::mt19937_64 gnr{ hw_rnd() };
}

namespace ffomsu
{

#ifndef M_PI
    #define M_E		    2.7182818284590452354	/* e */
    #define M_LOG2E	    1.4426950408889634074	/* log_2 e */
    #define M_LOG10E	0.43429448190325182765	/* log_10 e */
    #define M_LN2		0.69314718055994530942	/* log_e 2 */
    #define M_LN10		2.30258509299404568402	/* log_e 10 */
    #define M_PI		3.14159265358979323846	/* pi */
    #define M_PI_2		1.57079632679489661923	/* pi/2 */
    #define M_PI_4		0.78539816339744830962	/* pi/4 */
    #define M_1_PI		0.31830988618379067154	/* 1/pi */
    #define M_2_PI		0.63661977236758134308	/* 2/pi */
    #define M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */
    #define M_SQRT2	    1.41421356237309504880	/* sqrt(2) */
    #define M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2) */
#endif // M_PI

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

/// Случайное целое число в интервале [min; max]
size_t rand_std()
{
    return gnr();
}

/// Максимальное целое число, которое может вернуть ГПСЧ
size_t rand_max()
{
    return static_cast<size_t>( gnr.max() );
}

/// Минимальное целое число, которое может вернуть ГПСЧ
size_t rand_min()
{
    return static_cast<size_t>( gnr.min() );
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

void rand_re_seed()
{
    gnr.seed(hw_rnd());
}

void rand_re_seed(const size_t seed)
{
    gnr.seed(seed);
}

void show_rus_letters()
{
#ifdef _WIN32
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif // WIN32
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
