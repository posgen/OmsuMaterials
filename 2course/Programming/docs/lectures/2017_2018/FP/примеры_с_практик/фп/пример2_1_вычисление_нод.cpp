#include <iostream>
#include <cstdlib>

using namespace std;

double rate = 6.555;

/*
  Объявления функции с названием - nod
*/
int nod(int, int );

int main()
{
    int m, n;
    cout << "Введите два числа через пробел или перенос строки: ";

    // Цикл, показывающий один из вариантов обработки ошибок ввода
    do {
        cin >> m >> n;

        if ( cin.fail() ) {
            cin.clear();
            cin.ignore(1000, ' ');
            cout << "следующая попытка:\n";
        } else {
            break;
        }
    } while ( true );

    int result = nod(m, n);
    cout << "НОД: " << result << endl;
}

// Определение функции nod
int nod(int m, int n)
{
    if (n > m) {
        int tmp = m;
        m = n;
        n = tmp;
    }

    int r = m % n;

    while (r != 0) {
        m = n;
        n = r;

        r = m % n;
    }

    return abs(n);
}
