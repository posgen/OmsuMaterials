// Ввести последовательность целых чисел и определить суммы положительных и отрицательных чисел
// Ввод осуществляется до набора цифры 0. Используется цикл while.
#include <stdio.h>
#include <locale.h> // установка русской локали (нужна для ОС Windows)

int main()
{
    setlocale(LC_ALL, "RUS");

    int x = 1, positive_sum = 0, negative_sum = 0;

    while (x != 0) {
        printf("\nВведите целое число (0 - для остановки): ");
        scanf("%d", &x);

        if (x > 0)
            positive_sum += x;
        else
            negative_sum += x;
    }

    printf("Сумма положительных чисел: %d\n", positive_sum);
    printf("Сумма отрицательных чисел: %d\n", negative_sum);

    return 0;
}
