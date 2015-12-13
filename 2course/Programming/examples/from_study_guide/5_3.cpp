/*
    Демонстрация перегрузки функций. Возможна в языке C++, но не в C.

    Написать функцию выбора максимального элемента из массива для массивов
    4-х типов данных: int, long, float, double
*/
#include <iostream>

using namespace std;

int getMax(int size, int array[])
{
    int max = array[0], i = 0;

    cout << "getMax call, int version" << endl;
    for (; i < size; i++) {
        if (array[i] > max) max = array[i];
    }
    return max;
}

long getMax(int size, long array[])
{
    long max = array[0];
    int i = 0;

    cout << "getMax call, long version" << endl;
    for (; i < size; i++) {
        if (array[i] > max) max = array[i];
    }
    return max;
}

float getMax(int size, float array[])
{
    float max = array[0];
    int i = 0;

    cout << "getMax call, float version" << endl;
    for (; i < size; i++) {
        if (array[i] > max) max = array[i];
    }
    return max;
}

double getMax(int size, double array[])
{
    double max = array[0];
    int i = 0;

    cout << "getMax call, double version" << endl;
    for (; i < size; i++) {
        if (array[i] > max) max = array[i];
    }
    return max;
}

int main()
{
    int int_array[] = {1, 2, 3, 4, 5};
    long long_array[] = {12L, 44L, 5L, 22L, 35L};
    float float_array[] = {0.1, 0.2, 0.3, 0.4, 0.5};
    double double_array[] = {0.0001, 0.0002, 0.0003, 0.0004, 0.0005};

    cout << "getMax(5, int_array) = " << getMax(5, int_array) << endl;
    cout << "getMax(5, long_array) = " << getMax(5, long_array) << endl;
    cout << "getMax(5, float_array) = " << getMax(5, float_array) << endl;
    cout << "getMax(5, double_array) = " << getMax(5, double_array) << endl;

    return 0;
}

