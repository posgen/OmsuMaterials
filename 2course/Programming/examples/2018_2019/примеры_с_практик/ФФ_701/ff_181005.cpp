#include "ffhelpers.h"

using namespace ffomsu;
using namespace std;

/**
    Пример работы с ГПСЧ.
    Расчёт среднего значения из заданного количества случайных чисел
    на вручную задаваемом интервале.
*/

int main()
{
    show_rus_letters();
    double left, right;
    get_value(left, "Введите левую границу ");
    get_value(right, "Введите правую границу ");
    size_t kol_vo;
    get_value(kol_vo, "Введите количество чисел для вычисления среднего ");

    double summa = 0.0;
    for (size_t i = 1;i <= kol_vo; i++) {
        double rnd = rand_a_b_incl(left, right);
        summa += rnd;
    }

    print("Среднее значение на интервале [", left, "; ", right, "] равно ", summa/kol_vo);
}
