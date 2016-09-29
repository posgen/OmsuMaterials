/*
    Ввести и напечатать в обратном порядке последовательность чисел, количество которых заранее
    неизвестно. Количество значений определяется пользователем. Динамический массив задаётся с
    использованием функции malloc.
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h> // установка русской локали (нужна для ОС Windows)

int main()
{
    setlocale(LC_ALL, "RUS");

    int i, count;
    float *array;

    printf("Введите количество чисел: ");
    scanf("%d", &count);

    // динамически выделяем блок памяти под n элементов типа float
    array = (float *) malloc(count * sizeof(float));

    printf("Введите %d чисел\n", count);
    for (i = 0; i < count; i++) {
        printf("число номер %d = ", i + 1);
        scanf("%f", &array[i]);
    }


    printf("\nОбратный порядок:\n");
    for (i = count-1; i >= 0; i--) {
        printf("число номер %d = %f\n", i + 1, array[i]);
    }

    free(array); // освобождение динамически выделенной памяти
    return 0;
}

