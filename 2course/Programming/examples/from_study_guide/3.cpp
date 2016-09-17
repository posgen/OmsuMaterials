/*
    В прямоугольной матрице размером n x m определить индексы и значения элемента,
    который по модулю наименее отличается от среднего арифметического всех элементов
    матрицы. Значения элементов матрицы формировать в диапазоне от -1000 до 1000 с
    помощью генератора псевдослучайных чисел.

    Версия на C++
*/
#include <iostream>
#include <cmath>    // функция взятия модуля числа fabs
#include <cstdlib>  // для генератора псеводослучайных чисел: srand, rand, RAND_MAX. Используется С-библиотека
#include <ctime>    // текущее время в секундах используется для инициализации генератора
#include <clocale>

const int N_MAX = 10;
const int M_MAX = 10;

int main()
{
    std::setlocale(LC_ALL, "RUS");

    int n, m;
    double matrix[N_MAX][M_MAX], sum = 0.0, middle, min, diff;

    std::cout << "Введите количество строк: ";
    std::cin >> n;

    std::cout << "Введите количество столбцов: ";
    std::cin >> m;

    if (n > N_MAX || m > M_MAX) {
        std::cout << "Ошибка!\nЧисло n должно быть меньше чем " << N_MAX << ", число m должно быть меньше чем " << M_MAX;
        return -1;
    }

    if (n < 1 || m < 1) {
        std::cout << "Ошибка!\nn и m должны быть положительными";
        return -1;
    }

    // Инициализация генератора псевдослучайных чисел
    srand(time(nullptr));

    std::cout << "\nИсходная матрица:\n";

    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            matrix[i][j] = 2000 * ((double) rand()) / RAND_MAX - 1000;
            sum += matrix[i][j];

            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl; // переход на новую строку для лучшего отображения матрицы на экране
    }

    middle = sum / (n * m);
    std::cout << "\nСреднее значение элементов: " << middle << std::endl;

    min = fabs(matrix[0][0] - middle);

    int i_min = 0, j_min = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            diff = abs(matrix[i][j] - middle);

            if ( diff < min) {
                min = diff;
                i_min = i;
                j_min = j;
            }
        }
    }

    std::cout << "i_min = " << i_min << ", j_min = " << j_min << ", минимальное отклонение от среднего: " << matrix[i_min][j_min] << std::endl;
    return 0;
}
