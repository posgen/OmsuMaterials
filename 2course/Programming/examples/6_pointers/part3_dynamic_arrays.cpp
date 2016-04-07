/*
    Желательно ознакомиться с файлами part1_pointers.cpp и part2_pointers.cpp в той же директории, что и данный файл.

    Далее демонстрируется пример многомерных динамических массивов.
*/

#include <iostream>
#include <cstdlib>      // используется для функций srand, rand
#include <ctime>

using namespace std;

int main()
{
    srand( time(nullptr) ); // инициализация генератора псевдослучайных чисел, аналог srand( time(NULL) ) в C

    // Для объявления многомерного массива надо только указать количество звёздочек, равное его размерности
    // В данном случае объявляется двумерный массив целых чисел
    int **two_dim_array;

    // Далее нужно получить размерности массива. По аналогии с матрицами, обзовём их - числом строк и числом столбцов
    unsigned int rows_count, cols_count;

    cout << "Enter cols count: " << endl;
    cin >> cols_count;

    cout << "Enter rows count: " << endl;
    cin >> rows_count;

    // Затем начинаем выделять требуемую память для сохранения нужного количества элементов
    // Технически, двумерный массив в C++ состоит из массива указателей, каждый из которых
    // указывает на обычный одномерный массив.
    // Ниже в операторе new используется тип "int*" - это как раз и говорит о том, что
    // происходит создание массива указателей размером cols_count
    two_dim_array = new (nothrow) int*[cols_count];
    if ( two_dim_array == nullptr ) {
        // Желательно после каждого выделения памяти проверять, а было ли выделение успешно
        // Делается это путём сравнения указателя с его нулевым значением (nullptr в C++, NULL - в C)
        cerr << "Allocation memory error"; // cerr - аналогичен cout, но предназначен для вывода сообщений об ошибках
        return -1;
    }

    /*
        Когда всё прошло успешно, был получен массив указателей с числом элементов cols_count
        Теперь каждый элемент two_dim_array[i] сам по себе является обычным одномерным указателем (i изменяется от 0 до cols_count - 1)
        Этот факт можно даже продемонстрировать так:
            int i = 0, *p_int;   // объявляем индекс и обычный указатель на int
            p_int = two_dim_array[i]; // оба значения по сути - аналогичны

        Поэтому теперь каждому указателю two_dim_array[i] может быть выделен блок памяти для хранения конкретных значений
    */
    unsigned int i, j, k;
    for (i = 0; i < cols_count; ++i) {
        two_dim_array[i] = new (nothrow) int[rows_count];

        // новое выделение динамической памяти => новая проверка на успешность операции
        if ( two_dim_array[i] == nullptr ) {
            cerr << "Allocation memory error";
            return -1;
        }
    }

    /*
        Итак, после всех выделений памяти, у нас имеется массив из cols_count указателей,
        каждый их которых указывате на массив из rows_count целых чисел. На начало всей этой замысловатой структуры
        указывает переменная two_dim_array.

        Каждый указатель можно получить с помощью следующей индексации:
            two_dim_array[2] - третий указатель в их массиве (предполагается, что cols_count > 3)

        К каждому конкретному значению в массиве через двойную индексацию:
            two_dim_array[2][4] - доступ к пятому элементу третьего массива.
        Или на языке матриц, two_dim_array[2][4] - доступ к элемнту, расположенному в 3 строке, 5 столбце
    */

    // Далее заполним two_dim_array случайными числами и выведем на экран в виде матрицы
    cout << "The 2D matrix:" << endl;
    for (i = 0; i < cols_count; ++i) {
        for (j = 0; j < rows_count; ++j) {
            two_dim_array[i][j] = -15 + (rand() % 22);
            cout << two_dim_array[i][j] << "\t"; // печатаем текущий элемент и вставляем символ табуляции для отделения
                                            // значений строки друг от друга
        }
        cout << endl; // переход на новую строчку
    }

    /*
        После работы с динамическим массивом, хорошим тоном является освобождение всей используемой памяти.
        Для двумерного массива, освобождение памяти делается в порядке, обратном выделению:
            - сначало освобождаем для каждого массива
            - затем удаляем все массив указателей
    */
    for (i = 0; i < cols_count; ++i) {
        delete[] two_dim_array[i]; // действие, обратное строке 54
    }
    delete[] two_dim_array; // действие, обратное строке 35

    /*
        Далее пример (почти без комментариев) для объявления и заполнения, и какого-никакого,
        а вывода для трёхмерного массива действительных чисел.

        Поскольку третий размер вводить лень, предположим, что первая и вторая размерности равны cols_count,
        а третья - rows_count.
    */
    float ***three_dim_array;
    three_dim_array = new (nothrow) float**[cols_count];
    if (three_dim_array == nullptr) {
        cerr << "Allocation memory error";
        return -1;
    }

    for (i = 0; i < cols_count; ++i) {
        three_dim_array[i] = new (nothrow) float*[cols_count];
        if (three_dim_array[i] == nullptr) {
            cerr << "Allocation memory error";
            return -1;
        }

        for (j = 0; j < cols_count; ++j) {
            three_dim_array[i][j] = new (nothrow) float[rows_count];
            if (three_dim_array[i][j] == nullptr) {
                cerr << "Allocation memory error";
                return -1;
            }
        }
    }
    // тут выделение памяти под 3D массив закончено

    cout << endl << "3D array:" << endl;
    for (i = 0; i < cols_count; ++i) {
        cout << i + 1 << " layer:" << endl;
        for (j = 0; j < cols_count; ++j) {
            for (k = 0; k < rows_count; ++k) {
                three_dim_array[i][j][k] = float( rand() ) / RAND_MAX; // случайные действительные числа от 0 до 1
                cout << three_dim_array[i][j][k] << "\t";
            }
            cout << endl;
        }
    }

    // освобождение памяти для трёхмерного массива
    for (i = 0; i < cols_count; ++i) {
        for (j = 0; j < cols_count; ++j) {
            delete[] three_dim_array[i][j];
        }
        delete[] three_dim_array[i];
    }
    delete[] three_dim_array;

    return 0;
}
