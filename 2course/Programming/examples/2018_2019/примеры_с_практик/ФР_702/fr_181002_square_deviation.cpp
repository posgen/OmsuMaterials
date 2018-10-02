#include "ffhelpers.h"

using namespace std;
using namespace ffomsu;

int main()
{
    show_rus_letters();

    print("Имитация оценки погрешность некоторого физического эксперимента\n");
    print("с помощью расчёта средне квадратичного отклонения относительно средней величины.\n");

    double average, eps;
    get_value(average, "Введите среднее: ");
    get_value(eps, "Введите окрестность: ");

    size_t number_of_exps;
    get_value(number_of_exps, "Введите кол-во измерений: ");
    double sigma2 = 0.0;
    for (size_t i = 1; i <= number_of_exps; i++){
        double ri = rand_a_b_incl(average-eps, average+eps);
        sigma2 += pow(ri-average, 2);
    }

    print("Среднее квадратичное отклонение: ", sqrt(sigma2/number_of_exps));
}
