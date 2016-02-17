/*
    Построить и вывести на экран единичную диагональную матрицу (изменяемый порядок матрицы)
*/
#include <iostream>

using namespace std;

int main()
{
    int matrixOrder; // порядок матрицы

    cout << "Enter matrix order: ";
    cin >> matrixOrder;

    float **matr;
    // динамически выделяем блок памяти под matrixOrder элементов типа float* (массив указателей)
    matr = new float*[matrixOrder];

    int i, j;
    for (i = 0; i < matrixOrder; i++) {
        matr[i] = new float[matrixOrder];

        for (j = 0; j < matrixOrder; j++) {
            if (i != j)
                matr[i][j] = 0;
            else
                matr[i][j] = 1;
        }
    }

    cout << "The result" << endl;
    for (i = 0; i < matrixOrder; i++) {
        for (j = 0; j < matrixOrder; j++) {
            cout << matr[i][j] << "\t";
        }
        cout << endl;
        delete[] matr[i];
    }

    delete[] matr;
    return 0;
}
