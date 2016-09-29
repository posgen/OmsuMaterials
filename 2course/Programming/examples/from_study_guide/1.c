// Упорядочить три числа в порядке возрастания
#include <stdio.h> // функции ввода-вывода
#include <locale.h> // установка русской локали (нужна для ОС Windows)

int main()
{
    setlocale(LC_ALL, "RUS");

    int x, y, z;

    printf("Введите x: ");
    scanf("%d", &x);

    printf("\nВведите y: ");
    scanf("%d", &y);

    printf("\nВведите z: ");
    scanf("%d", &z);

    printf("В порядке возрастания: \n");

    if (x > y) {
        if (y > z) {
            printf("z = %d\n", z);
            printf("y = %d\n", y);
            printf("x = %d\n", x);
        } else {
            printf("y = %d\n", y);

            if (x > z) {
                printf("z = %d\n", z);
                printf("x = %d\n", x);
            } else {
                printf("x = %d\n", x);
                printf("z = %d\n", z);
            }
        }
    } else {
        if (x > z) {
            printf("z = %d\n", z);
            printf("x = %d\n", x);
            printf("y = %d\n", y);
        } else {
            printf("x = %d\n", x);

            if (y > z) {
                printf("z = %d\n", z);
                printf("y = %d\n", y);
            } else {
                printf("y = %d\n", y);
                printf("z = %d\n", z);
            }
        }
    }

    return 0;
}
