#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

/*
    Пример функции, принимающей аргументы как по значению,
    так и по ссылке.
*/
void transform_to_spheric(const double x1, const double y1, const double z1,
                          double& r, double& theta, double& phi)
{
    r     = sqrt(x1*x1 + y1*y1 + z1*z1);
    theta = acos( z1 / r );
    phi   = atan( y1 / x1 );
}

int main()
{
    double x, y, z;

    cout << "Введите значение x = ";
    cin >> x;

    cout << "Введите значение y = ";
    cin >> y;

    cout << "Введите значение z = ";
    cin >> z;
    cout << "\n";

    // Следующие три переменных получают значения
    // при вывове функции transform_to_spheric
    double r1, th1, ph1;
    transform_to_spheric(x, y, z, r1, th1, ph1);

    cout << "r     = " << r1 << "\n";
    cout << "theta = " << th1 << "\n";
    cout << "phi   = " << ph1 << "\n";
}
