#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>


#include "liblect6.h"

void pretty_print(const FP003Array);
void init_by_squares(FP003Array&);
FP003Array make_array(size_t array_size, int start, int step);
void swap_array(FP003Array& lhs, FP003Array& rhs);
bool cmp_desc(int& lhs, int& rhs);

/**
    Пример функциональные объектов (функторы).
    Технически - просто класс (составной тип), в котором
    перегружен оператор круглых скобок - *()*

    Для простой линейной зависимости:
        u(x) = a*x + b;

    Сначало - простая функция.
*/
double u(double x, double a, double b)
{
    return a * x + b;
}
/// А вот и они.
class LinearFn
{
public:
    const double a, b;

    double operator()(double x)
    {
        return a * x + b;
    }
};

class ExpFn
{
public:
    ExpFn(double a, double b) :
        exp_a{std::exp(a)}, exp_b{std::exp(b)}
    {}

    double operator()(double x)
    {
        return std::pow(exp_a, x) * exp_b;
    }

private:
    double exp_a, exp_b;
};

int main()
{
    using namespace std;

    /**
    /// В финальной версии такой страшный код уже не нужен
    FP003Array examp1(10);

    examp1[0] = 16;
    examp1[1] = -3;
    examp1[2] = -5;
    examp1[3] = 4;
    examp1[4] = 4;
    examp1[5] = 9;
    examp1[6] = 17;
    examp1[7] = 11;
    examp1[8] = 2;
    examp1[9] = 4;
    */
    /// Ведь можно теперь делать так
    FP003Array examp1 = {16, -3, -5, 4, 4, 9, 17, 11, 2, 4};

    /// Используем различные алгоритмы для коллекций из <algorithm>
    cout << "Before sorting examp1 contains:\n";
    pretty_print(examp1);
    /// стандартная сортировка
    std::sort(examp1.begin(), examp1.end());
    /// или можно только часть массива сортировать:
    //std::sort(examp1.begin(), examp1.end() - 3);
    cout << "After sorting:\n";
    pretty_print(examp1);

    FP003Array examp2(14);
    /// присвоение всем элементам массива одного и того же числа
    std::fill(examp2.begin(), examp2.end(), 7);
    pretty_print(examp2);

    /// подсчёт количества элементов, равным конкретному значению
    int count_of_four = std::count(examp1.begin(), examp1.end(), 4);
    cout << count_of_four << " numbers equals to 4" << endl;

    /// поиск конкретного значения в массиве и получение итератора на него, если найдено
    int number_to_find = 16;
    FP003Array::Iterator it_found = std::find(examp1.begin(), examp1.end(), number_to_find);
    /// если не найдено - будет возвращено значение итератора, указываеющее на конец коллекции
    if (it_found != examp1.end()) {
        cout << "number " << number_to_find << " found at " << (it_found - examp1.begin() + 1) << " place" << endl;
    } else {
        cout << "number " << number_to_find << " not found" << endl;
    }

    cout << endl;
    ///#########Демонстрация использования функциональных объектов#########
    LinearFn u1 = {5, 10}, u2 = {-3, 2}, u3{3.5, -0.5};
    cout << "5*x + 10 (at x = 2): " << u1(2) << endl;
    cout << "5*x + 10 (at x = 2): " << u(2, 5, 10) << endl;

    double res = u1(3.5) + u2(-1.4) * u3(0.33);
    double res2 = u(3.5, 5, 10) + u(-1.4, -3, 2) * u(0.33, 3.5, -0.5);
    cout << res << ", " << res2 << endl;

    ExpFn ue1 = {3.5, -1.7};
    cout << "ue1(4.5) = " << ue1(4.5) << endl << endl;

    /// Генератор псевдо случайных чисел - пример из стандартной библиотеки
    mt19937_64 gnr{ static_cast<size_t>(time(nullptr)) };
    /// создание генератора более интересным способом:
    // mt19937_64 gnr{ random_device{}() };
    cout << gnr() << ", " << gnr() << endl;
    ///###########################
}

void pretty_print(const FP003Array obj)
{
    std::cout << "[";
    const size_t len = obj.length();

    for (size_t i = 0; i < obj.length(); i++) {
        const auto extra_str = (i == (len - 1)) ? "" : ", ";
        std::cout << obj[i] << extra_str;
    }
    std::cout << "]" << std::endl;
}

void init_by_squares(FP003Array& obj)
{
    for (size_t i = 0; i < obj.length(); i++) {
        obj[i] = i * i;
    }
}

FP003Array make_array(size_t array_size, int start, int step)
{
  FP003Array new_obj(array_size);

  for (size_t i = 0; i < new_obj.length(); i++) {
    new_obj[i] = start + i * step;
  }

  return new_obj;
}

void swap_array(FP003Array& lhs, FP003Array& rhs)
{
    FP003Array tmp = std::move(lhs);
    lhs = std::move(rhs);
    rhs = std::move(tmp);
}

bool cmp_desc(int& lhs, int& rhs)
{
    return lhs > rhs;
}

