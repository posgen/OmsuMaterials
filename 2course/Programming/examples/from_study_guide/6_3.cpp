/*
    Определить функцию, которая упорядочивает значения трёх переданных ей элементов целого типа.
    Использование указателей. Показан один из способов менять внутри функций значения переданных элементов.
    Версия для C++.
*/
#include <iostream>
#include <clocale> // установка русской локали (нужна для ОС Windows)


void rank2(int *x, int *y)
{
    int tmp;

    if (*x > *y) {
        tmp = *x;
        *x = *y;
        *y = tmp;
    }
}


void rank3(int *x, int *y, int *z)
{
    rank2(x, y);
    rank2(y, z);
    rank2(x, z);
}


int main()
{
    std::setlocale(LC_ALL, "RUS");

    int i, j, k;

    std::cout << "Введите i: ";
    std::cin >> i;

    std::cout << "Введите j: ";
    std::cin >> j;

    std::cout << "Введите k: ";
    std::cin >> k;

    rank3(&i, &j, &k);

    std::cout << "После обработки:\ni = " << i << ", j = " << j << ", k = " << k << "\n";

    return 0;
}
