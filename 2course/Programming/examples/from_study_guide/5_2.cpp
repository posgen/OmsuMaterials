/*
    Написать функцию для перестановки в обратном порядке значений элементов целочисленного массива.
    В качестве вспомогательной определить функцию для обмена значений двух элементов массива.
*/
#include <iostream>
#include <clocale>

// Функция перестановки двух элементов в массиве.
// Тип возращаемого значения - void, означающий, что функция не возращает никакого значения (не требуется явный "return value;").
// Стоит заметить, что при передаче массива в качестве аргумента функции - размерность можно не указывать(верно только для одномерных массивов).
void array_elems_swap(int array[], int pos1, int pos2)
{
    int tmp = array[pos1];
    array[pos1] = array[pos2];
    array[pos2] = tmp;
}


void reverse(int array[], int size)
{
    int i;
    for (i = 0; i < size / 2; i++) {
        array_elems_swap(array, i, size - i - 1);
    }
}


void printArray(int array[], int size)
{
    int i;
    for (i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
}

int main()
{
    int line[] = { 5, 6, 2, 4, 9, 2, 1 }, size;
    size = sizeof(line) / sizeof(line[0]);

    std::cout << "Исходный массив:\n";
    printArray(line, size);

    reverse(line, size);

    std::cout << "\nИтоговый массив:\n";
    printArray(line, size);

    return 0;
}
