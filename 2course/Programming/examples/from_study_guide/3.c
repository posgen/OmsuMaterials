/*
    В прямоугольной матрице размером n x m определить индексы и значения элемента,
    который по модулю наименее отличается от среднего арифметического всех элементов
    матрицы. Значения элементов матрицы формировать в диапазоне от -1000 до 1000 с 
    помощью генератора псевдослучайных чисел.
*/
#include <stdio.h>
#include <math.h>    // функция взятия модуля числа fabs
#include <stdlib.h>  // для генератора псеводослучайных чисел: srand, rand, RAND_MAX
#include <time.h>    // текущее время в секундах используется для инициализации генератора

#define N_MAX 10
#define M_MAX 10

int main()
{
    int i, j, n, m, i_min, j_min;
    double matrix[N_MAX][M_MAX], sum = 0.0, middle, min, diff;

    printf("Enter rows count: ");
    scanf("%d", &n);

    printf("\nEnter columns count: ");
    scanf("%d", &m);

    if (n > N_MAX || m > M_MAX) {
        printf("\nError!\nn should be less than %d, m should be less than %d", N_MAX, M_MAX);
        return -1;
    }

    if (n < 1 || m < 1) {
        printf("\nError!\nn and m should be positive");
        return -1;
    }

    // Инициализация генератора псевдослучайных чисел
    srand(time(NULL));

    printf("\nThe matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            matrix[i][j] = 2000 * ((double) rand()) / RAND_MAX - 1000;
            sum += matrix[i][j];

            printf("%8.2f", matrix[i][j]); 
        }
        printf("\n"); // переход на новую строку для лучшего отображения матрицы на экране
    }

    middle = sum / (n * m);
    printf("\nThe average is %8.2f\n", middle);

    min = fabs(matrix[0][0] - middle);
    i_min = j_min = 0;

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            diff = fabs(matrix[i][j] - middle);

            if ( diff < min) {
                min = diff;
                i_min = i;
                j_min = j;
            }
        }
    }

    printf("i_min = %d, j_min = %d, min value = %8.2f\n", i_min, j_min, matrix[i_min][j_min]);
    return 0;
}
