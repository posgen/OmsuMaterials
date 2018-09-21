#include "ffhelpers.h"

using namespace ffomsu;
using namespace std;

int main()
{
    print("a*x^2 + b*x + c = 0\n");
    print("Введите коэффициенты a,b,c:\n");

    double a, b, c;
    get_value(a);
    get_value(b);
    get_value(c);

    if (a != 0.0) {
        double diskriminant=b*b - 4*a*c;

        if (diskriminant < 0.0) {
            print("Действительных корней нет\n",
                   diskriminant, " < 0");
        } else {
            double x1, x2;
            x1 = (-b+sqrt(diskriminant))/(2*a);
            x2 = (-b-sqrt(diskriminant))/(2*a);
            print("x1 = ", x1, "\n",
                  "x2 = ", x2);
        }
    } else {
        print("a = 0, работать не буду");
    }
}
