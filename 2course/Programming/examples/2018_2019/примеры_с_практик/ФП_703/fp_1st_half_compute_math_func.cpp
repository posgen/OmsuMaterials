#include "ffhelpers.h"

using namespace ffomsu;
using namespace std;

int main()
{
    print("Список функций\n");
    print("1) Sin;\n2) Cos;\n3) Ln;\n4) Log;\n5) Exp;\n6) Sqrt;\n7) Abs;\n");

    int number;
    get_value(number, "Выберите функцию: ");

    double in, out_f;
    get_value(in, "Введите аргумент: ");

    switch (number) {
        case 1:
            out_f = sin(in);
            break;
        case 2:
            out_f = cos(in);
            break;
        case 3:
            out_f = log(in);
            break;
        case 4:
            out_f = log10(in);
            break;
        case 5:
            out_f = exp(in);
            break;
        case 6:
            out_f = sqrt(in);
            break;
        case 7:
            out_f = abs(in);
            break;
        default:
            print("Неправильно выбранная функция\n");
    }

    print("Значение при выбранном аргументе ", in , " равно ", out_f);
}

