/*
    Построить и вывести на экран единичную диагональную матрицу (изменяемый порядок матрицы)
*/
#include <iostream>

using namespace std;

int main()
{
    size_t matrix_order; // порядок матрицы

    cout << "Введите размер квадратной матрицы: ";
    cin >> matrix_order;

    double **matr;
    // динамически выделяем блок памяти под matrixOrder элементов типа float* (массив указателей)
    matr = new float*[matrix_order];

    for (size_t i = 0; i < matrix_order; i++) {
        matr[i] = new double[matrix_order];

        for (size_t j = 0; j < matrix_order; j++) {
            if (i != j)
                matr[i][j] = 0;
            else
                matr[i][j] = 1;
        }
    }

    // Вывод и одновременное удаление двумерного массива
    cout << "Созданная матрица:\n";
    for (size_t i = 0; i < matrix_order; i++) {
        for (size_t j = 0; j < matrix_order; j++) {
            cout << matr[i][j] << "\t";
        }
        cout << endl;
        delete[] matr[i];
    }
    delete[] matr;

    return 0;
}
