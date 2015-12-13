// Ввести последовательность целых чисел и определить суммы положительных и отрицательных чисел
// Ввод осуществляется до набора цифры 0. Используется цикл while.
#include <stdio.h>

int main()
{
    int x = 1, positive_sum = 0, negative_sum = 0;

    while (x != 0) {
        printf("\nEnter number (0 - to stop): ");
        scanf("%d", &x);

        if (x > 0)
            positive_sum += x;
        else
            negative_sum += x;
    }

    printf("The sum of positive numbers is: %d\n", positive_sum);
    printf("The sum of negative numbers is: %d\n", negative_sum);

    return 0;
}
