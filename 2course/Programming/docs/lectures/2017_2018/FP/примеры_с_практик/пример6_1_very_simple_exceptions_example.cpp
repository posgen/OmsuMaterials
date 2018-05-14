/**
    Очень простой вводный пример на демонстрацию исключений
*/

#include <iostream>
#include <exception>
#include <string>

struct MyError
{
    std::string msg;
};

class Test
{
public:
    ~Test()
    {
        std::cout << "Вызван деструктор\n";
    }
};

double sin_by_sharnin(double x)
{
    const size_t fakt_3 = 6,
                 fakt_5 = 120;
    Test t1, t2;

    if (x == 1.0) {
        throw MyError{"Неправильный аргумент"};
    }

    if (x == 2.0) {
        /// ради теста, выбрасываем исключение типа double
        /// не стоит так делать в рабочих программах
        throw 5.78;
    }

    if (x == 3.0) {
        /// выбрасываем базовый тип исключений для всей стандартной библиотеки
        throw std::exception{};
    }

    t2 = t1; /// демонстрация работы деструкторов, даже при выбросе исключения
    return x - (x*x*x)/fakt_3 + (x*x*x*x*x)/fakt_5;
}

void find_sins(int code)
{
    std::cout << "sin(1.57) = "
        << sin_by_sharnin(1.57) << "\n";

    std::cout << "sin(0.87) = "
        << sin_by_sharnin(0.87) << "\n";

    if (code == 1) {
        std::cout << "sin(1.0) = "
            << sin_by_sharnin(1.0) << "\n";
    } else if (code == 2) {
        std::cout << "sin(2.0) = "
            << sin_by_sharnin(2.0) << "\n";
    } else {
        std::cout << "sin(3.0) = "
            << sin_by_sharnin(3.0) << "\n";
    }
}

int main()
{
    using namespace std;

    int code;
    cout << "Введите целое число: ";
    cin >> code;

    Test t1, t2;
    t2 = t1;

    try {
        find_sins(code);
    }
    catch (const MyError& err) {
        cout << "Исключение перехвачено c сообщением: ";
        cout << err.msg << "\n";
    }
    catch (const double&) {
        cout << "Исключение типа double перехвачено\n";
    }
    catch (const std::exception& exc) {
        cout << "Исключение типа exception перехвачено\n";
        cout << exc.what() << "\n";
    }
}
