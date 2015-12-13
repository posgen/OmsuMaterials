/*
    Ввести и напечатать в обратном порядке последовательность чисел, количество которых заранее
    неизвестно. Количество значений определяется пользователем. Динамический массив задаётся с
    использованием функции malloc.
*/
#include <stdio.h>
#include <stdlib.h>


int main()
{
    int i, count;
    float *array;

    printf("Enter numbers count: ");
    scanf("%d", &count);

    // динамически выделяем блок памяти под n элементов типа float
    array = (float *) malloc(count * sizeof(float));

    printf("Enter %d numbers\n", count);
    for (i = 0; i < count; i++) {
        printf("number %d = ", i + 1);
        scanf("%f", &array[i]);
    }


    printf("\nReverse order:\n");
    for (i = count-1; i >= 0; i--) {
        printf("number %d = %f\n", i + 1, array[i]);
    }

    free(array); // освобождение динамически выделенной памяти
    return 0;
}

