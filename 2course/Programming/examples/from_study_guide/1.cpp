/*
  Упорядочить три числа в порядке возрастания.
  C++ версия
*/

#include <iostream> // подключение ввода/вывода в консоль
#include <clocale>  // Для Windows - подключение вывода русских букв в консоль

int main()
{
    std::setlocale(LC_ALL, "RUS");

    int x, y, z;

    std::cout << "x: ";
    std::cin >> x;

    std::cout << "y: ";
    std::cin >> y;

    std::cout << "z: ";
    std::cin >> z;

    // Печатаем некоторый текст с переносом
    std::cout << "Результат: \n";

    if (x > y) {
        if (y > z) {
            // Обращаем внимание, как форматируется строка для вывода на экран. В частности, отступы
            std::cout << "z = " << z << "\n";
            std::cout << "y = " << y << "\n";
            std::cout << "x = " << x << "\n";
        } else {
            std::cout << "y = " << y << "\n";

            if (x > z) {
                std::cout << "z = " << z << "\n";
                std::cout << "x = " << x << "\n";
            } else {
                std::cout << "x = " << x << "\n";
                std::cout << "z = " << z << "\n";
            }
        }
    } else {
        if (x > z) {
            std::cout << "z = " << z << "\n";
            std::cout << "x = " << x << "\n";
            printf("y = %d\n", y);
        } else {
            std::cout << "x = " << x << "\n";

            if (y > z) {
                std::cout << "z = " << z << "\n";
                std::cout << "y = " << y << "\n";
            } else {
                std::cout << "y = " << y << "\n";
                std::cout << "z = " << z << "\n";
            }
        }
    }

    return 0;
}
