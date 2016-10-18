/*
    Ввести и напечатать в обратном порядке последовательность чисел, количество которых заранее
    неизвестно. Количество значений определяется пользователем. Динамический массив задаётся с
    использованием функции new (пример на языке C++).
*/
#include <iostream>
#include <clocale>

using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");

    size_t nums_count;
    float *nums_array;

    cout << "Введите количество чисел: ";
    cin >> nums_count;

    // динамически выделяем блок памяти под n элементов типа float
    nums_array = new float[nums_count];

    cout << "Введите " << nums_count << " чисел" << endl;
    for (size_t i = 0; i < nums_count; i++) {
        cout << "число номер " << i + 1 << " = ";
        cin >> nums_array[i];
    }


    cout << endl << "\nОбратный порядок:" << endl;
    for (int i = nums_count-1; i >= 0; i--) {
        cout << "число номер " << i + 1 << " = " << nums_array[i] << endl;
    }

    delete[] nums_array; // освобождение динамически выделенной памяти
    return 0;
}
