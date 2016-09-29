/*
    Сформировать и вывести на печать нижную треугольную матрицы.

    Матрица a_ij называется нижней треугольной, если при i < j
    a_ij = 0. Здесь i - номер строки, j - номер столбца (1 <= i <= rowsNum, 1 <= j <= colsNum, rowsNum - число строк, colsNum - число столбцов)
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h> // установка русской локали (нужна для ОС Windows)

int main()
{
    setlocale(LC_ALL, "RUS");

    int i, j, rowsNum, colsNum, jRow;
    double **triMatr;

    printf("Введите количество строк: ");
    scanf("%d", &rowsNum);
    printf("Введите количество столбцов: "); // количество столбцов
    scanf("%d", &colsNum);

    // Выделяем память под массив указателей
    triMatr = (double **) malloc(rowsNum * (sizeof(double*)));
    /*
        Если память выделить невозможно, функции malloc / calloc возращают нулевой указатель.
        В языке С этот указатель задан константой NULL
    */
    if ( triMatr == NULL ) {
        printf("Ошибка выделения памяти\n");
        return -1;
    }

    for (i = 0; i < rowsNum; i++) {
        jRow = (i < colsNum) ? i + 1: colsNum;
        // Выделяем память для каждой строки
        triMatr[i] = (double *) malloc(jRow * sizeof(double));
        if ( triMatr[i] == NULL ) {
            printf("Ошибка выделения памяти\n");
            exit(1); // аварийное завершение программы, все ранее выделенные ресурсы возращаются системе
        }

        for (j = 0; j < jRow; j++) {
            triMatr[i][j] = i + 1;
        }
    }

    printf("Итоговая матрица:\n");
    for (i = 0; i < rowsNum; i++) {
        jRow = (i < colsNum) ? i + 1: colsNum;
        for (j = 0; j < jRow; j++) {
            printf("%.2f ", triMatr[i][j]);
        }
        printf("\n");

        // После печати всех элементов в строке, освобождаем память под неё
        free(triMatr[i]);
    }

    // Осбовождаем память под массив указателей
    free(triMatr);
    return 0;
}
