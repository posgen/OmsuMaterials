/*
    Пример разложения (x + y)^n на множители
*/

#include <iostream>
#include <cstdlib>

using namespace std;

/*
  Аргументы функции объявлены неизменяемыми (константными),
  поскольку внутри функции ни n, ни k - не меняются.
*/
unsigned long long binom_coef(const unsigned n, const unsigned k)
{
    if ( (n == 0) || (k > n ) ) {
        return 0;
    }

    unsigned long long result = 1;

    for (unsigned i = (n - k + 1); i <= n; ++i) {
        result *= i;
    }

    for (unsigned i = 2; i <= k; ++i) {
        result /= i;
    }

    return result;
}


int main()
{
    unsigned number;
    cout << "Введите целое число: ";

    do {
        cin >> number;

        if ( cin.fail() ) {
            cin.clear();
            cin.ignore(1000, ' ');
            cout << "\nВведено не число. Попробуйте снова: ";
        } else {
            break;
        }
    } while ( true );

    cout << "\n(x + y)^" << number << " = ";
    for (unsigned k = 0; k <= number; ++k) {
        if ( k == 0 ) {
            cout << "(x^" << number << ") ";
            continue;
        }

        if ( k == number ) {
            cout << " + " << "(y^" << number << ") ";
            continue;
        }

        unsigned long long coef = binom_coef(number, k);
        cout << " + " << coef << "(x^" << (number - k)
             << ") (y^" << k << ") ";
    }

    cout << "\nГотово!\n";
}
