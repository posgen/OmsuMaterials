/*
    Ввести и напечатать в обратном порядке последовательность чисел, количество которых заранее
    неизвестно. Количество значений определяется пользователем. Динамический массив задаётся с
    использованием функции new (пример на языке C++).
*/
#include <iostream>

using namespace std;

int main()
{
    int i, count;
    float *array;

    cout << "Enter numbers count: ";
    cin >> count;

    // динамически выделяем блок памяти под n элементов типа float
    array = new float[count];

    cout << "Enter " << count << "numbers" << endl;
    for (i = 0; i < count; i++) {
        cout << "number " << i + 1 << " = ";
        cin >> array[i];
    }


    cout << endl << "\nReverse order:" << endl;
    for (i = count-1; i >= 0; i--) {
        cout << "number " << i + 1 << " = " << array[i] << endl;
    }

    delete[] array; // освобождение динамически выделенной памяти
    return 0;
}

