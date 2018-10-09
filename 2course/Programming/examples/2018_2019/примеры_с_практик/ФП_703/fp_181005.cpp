/**
    Пример на использование ГПСЧ и создания функции.
*/

#include "ffhelpers.h"

using namespace std;
using namespace ffomsu;

/**
    Функция для расчёта биноминальных коэффициентов.

    Принимает 2 параметра:
        * n - 0, 1, 2, 3, и так далее
        * k - меняется от 0 до n

    Возращает число, рассчитанное по формуле:
        / n \        n!
        |   | = ------------
        \ k /    k!(n - k)!
*/
size_t binom_coef(const size_t n, const size_t k)
{
    if (k == 0 or n == k) {
        return 1;
    }

    size_t numerator = 1, denominator = 1;
    for (size_t i = k + 1; i <= n; i++ ) {
        numerator *= i;
    }

    for (size_t i = 2; i <= n - k; i++ ) {
        denominator *= i;
    }

    return numerator / denominator;
}

int main()
{
    print("Часть 1.\nПрограмма для расчёта вероятности выпадения орла и решки.\n");
    print("Введите количество бросков монеты:\n");
    size_t cycle;
    get_value(cycle);

    size_t orel = 0, reshka = 0;
    for (size_t i = 1; i <= cycle; i++ ){
        if (rand_a_b_incl() <= 0.5) {
            orel++;
        } else {
            reshka++;
        }
    }
    print("Вероятность выпадения орла: ", double(orel)/cycle, "\n");
    print("Вероятность выпадения решки: ", double(reshka)/cycle,  "\n");


    print("Часть 2\nВывод треугольника Паскаля\n");
    size_t last_line_number;
    get_value(last_line_number, "Введите последний индекс строки треугольника: ");

    /// Цикл, отвечающий за вывод треугольника Паскаля на экран
    for (size_t n = 0; n <= last_line_number; n++) {
        for (size_t k = 0; k <= n; k++) {
            print(binom_coef(n, k), " ");
        }
        print("\n");
    }
}
