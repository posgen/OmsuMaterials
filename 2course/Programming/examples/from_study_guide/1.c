// Упорядочить три числа в порядке возрастания
#include <stdio.h>

int main()
{
    int x, y, z;

    printf("x: ");
    scanf("%d", &x);

    printf("\ny: ");
    scanf("%d", &y);

    printf("\nz: ");
    scanf("%d", &z);

    printf("Result: \n");

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
