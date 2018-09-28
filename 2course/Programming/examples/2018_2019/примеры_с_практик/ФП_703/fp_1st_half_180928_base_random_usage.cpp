#include "ffhelpers.h"

using namespace std;
using namespace ffomsu;

double srednee(const int left, const int right, const int col)
{
    double summ =0.0;

    for (int i =1; i<=col; i++){
        int slchislo = rand_a_b_excl(left, right);
        summ += slchislo;
    }

    return summ/col;
}


int main()
{
    const int COL = 10;

    print("введите диапазон: \n");

    int  left, right;
    get_value(left);
    get_value(right);
    /*
    int sum = 0;
    for (int i = 1; i<=COL; i++){
        int slchislo = rand_a_b_excl(left, right);
        print("Случайное целое число :", slchislo , "\n");
        sum += slchislo;
    }
    print("Сумма всех значений: ", sum, "\n");
    double sred = double (sum)/COL;
    print("Среднее арифметическое: ", sred);
    */

    print("Среднее от случайных чисел в диапазоне [", left, "; ", right, "]: ", srednee(left, right, COL));
}
