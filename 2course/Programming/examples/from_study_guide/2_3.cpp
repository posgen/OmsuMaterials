/*
    Ввести последовательность целых чисел и определить суммы положительных и отрицательных чисел
    Ввод осуществляется до набора цифры 0. Используется цикл for.
    Версия C++
*/

#include <iostream> // подключение ввода/вывода в консоль
#include <clocale>  // Для Windows - подключение вывода русских букв в консоль

int main()
{
    std::setlocale(LC_ALL, "RUS"); // Установка русской локали для консоли в Windows

    int x = 1, positive_sum = 0, negative_sum = 0;

    for(; x != 0;) {
        std::cout << "Введите число (0 - для прекращения ввода): ";
        std::cin >> x;

        if (x > 0)
            positive_sum += x;
        else
            negative_sum += x;
    }

    std::cout << "Сумма положительных чисел: " << positive_sum << "\n";
    std::cout << "Сумма отрицательных чисел: " << negative_sum << "\n";

    return 0;
}
