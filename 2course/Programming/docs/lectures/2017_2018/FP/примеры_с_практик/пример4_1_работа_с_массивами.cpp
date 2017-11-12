/*
    Пример применения использования библиотеки <algorithm>
    для типовых операций с массивами
*/

#include <iostream>
#include <ctime>  /// Библиотека работы со временем
#include <cmath>  /// Библиотека работы с мат. функциями
#include <random> /// Библиотека с различными генераторами
#include <algorithm> /// Библиотека с функциями по обработке массивов (плюс некоторые обобщённые функции)

using namespace std;

const size_t ARR_SZ = 9;

/*
    Функция для получения случайных числел из предыдущего примера
*/
double real_rnd_0_1();
double real_rnd_a_b(double a, double b);

/**
    Собственная функция для указания порядка сортировки.
    В примере - сортировка целых значений по убыванию.

    Сама функция должна принимать два аргумента сортируемого
    типа (в данном случае - int). И возращать значение *true*,
    если значение в аргументе first должно быть в массиве раньше,
    чем значение в аргументе second; и *false* - в противном случае.
*/
bool descenting_sort_ints(int first, int second)
{
    return first > second;
}

/**
    Функция для сортировки массивов типа double по возрастанию
    модулей каждого элемента.
*/
bool ascenting_doubles_by_abs(double first, double second)
{
    return abs(first) < abs(second);
}

int main()
{
    /// Создаём массив int'ов с числом элементов ARR_SZ
    int arr_ints[ARR_SZ];
    /// Заполняем его случайными числами в диапазоне [-10; 10]
    for (size_t i = 0; i < ARR_SZ; ++i) {
        arr_ints[i] = real_rnd_a_b(-10, 10);
    }

    cout << "Исходный массив целых чисел:\n";
    for (int elem : arr_ints) {
        cout << elem << ' ';
    }
    cout << '\n';

    /// Применяем функцию сортировки из <algorithm>
    /// По умочанию происходит сортировка по возрастанию
    sort(arr_ints, arr_ints + ARR_SZ);

    cout << "Отсортированный по возрастанию массив целых чисел:\n";
    for (int elem : arr_ints) {
        cout << elem << ' ';
    }
    cout << '\n';

    /// Ещё раз заполняем миссив arr_ints случайными числами в диапазоне [-15; 14]
    for (size_t i = 0; i < ARR_SZ; ++i) {
        arr_ints[i] = real_rnd_a_b(-15, 14);
    }

    cout << "\nМассив целых чисел перед второ сортировкой:\n";
    for (int elem : arr_ints) {
        cout << elem << ' ';
    }
    cout << '\n';

    /// Применяем функцию сортировки из <algorithm>
    /// с собственной функцией сравнения элементов.
    /// По следний аргумент - название функции сравнения
    sort(arr_ints, arr_ints + ARR_SZ, descenting_sort_ints);

    cout << "Отсортированный по убыванию массив целых чисел:\n";
    for (int elem : arr_ints) {
        cout << elem << ' ';
    }
    cout << '\n';

    /**
        Зададим квадратную двумерную матрицу действительных чисел
    */
    double reals_2D[ARR_SZ][ARR_SZ];
    for (size_t i = 0; i < ARR_SZ; ++i) {
        for (size_t j = 0; j < ARR_SZ; ++j) {
            reals_2D[i][j] = real_rnd_a_b(-105.0, 105.0);
        }
    }

    cout << "\nИсходная матрица:\n";
    for (const auto& row : reals_2D) { // Этот цикл переберает все строчки
        for (double elem : row) {    // Этот - все элементы в конкретной строке
            cout << elem << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    /// И отсортируем половину её строк по возрастанию модуля каждого элемента
    for (size_t i = 0; i <= ARR_SZ / 2; ++i) {
        sort(reals_2D[i], reals_2D[i] + ARR_SZ, ascenting_doubles_by_abs);
    }

    cout << "Матрица после частичной сортировки:\n";
    for (const auto& row : reals_2D) { // Этот цикл переберает все строчки
        for (double elem : row) {    // Этот - все элементы в конкретной строке
            cout << elem << " ";
        }
        cout << "\n";
    }
    cout << "\n";


    int ints_to_search[] = {-4, 5, -3, 55, 6, -3, -11, 18, 19, 21, 89, 101, -5};
    int key;

    cout << "\nВведите целое число для поиска: ";
    cin >> key;
    /**
        Функция find - указываем диапазон для поиска [fisrt, last)
        и значение, которое ищем.
        Возращается указатель на найденый элемент, либо значение указателя last
    */
    int *last = ints_to_search + 13;
    int *found_elem = find(ints_to_search, last, key);
    if (found_elem != last) {
        cout << "Значение " << key << " содержится в массиве ints_to_search\n";
    } else {
        cout << "Значение " << key << " не найдено в массиве ints_to_search\n";
    }

    /**
        Функция count - найти количество конкретного значения в массиве
    */
    cout << "\nЗначение -3 в массиве ints_to_search появляется ";
    int times_in_arr = count(ints_to_search, ints_to_search + 13, -3);
    if (times_in_arr >= 2 && times_in_arr <= 4) {
        cout << times_in_arr << " раза\n";
    } else {
        cout << times_in_arr << " раз\n";
    }

    /**
        И даже для того, чтобы обменять значение в двух переменных -
        в <algorithm> есть стандартная функция swap
    */
    double val1 = 55.789, val2 = -102.488;
    swap(val1, val2);
    cout << "\nЗначение val1 = " << val1 << "\n";
    cout << "Значение val2 = " << val2 << "\n";
}

double real_rnd_0_1()
{
    static mt19937_64 gener( time(nullptr) );
    static unsigned long long max_num = gener.max();

    return static_cast<double>( gener() ) / max_num;
}

double real_rnd_a_b(double a, double b)
{
    return (b - a) * real_rnd_0_1() + a;
}
