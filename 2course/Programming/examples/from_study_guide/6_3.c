/*
    Определить функцию, которая упорядочивает значения трёх переданных ей элементов целого типа.
    Использование указателей. Показан один из способов менять внутри функций значения переданных элементов.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void rank2(int *x, int *y)
{
    int tmp;

    if (*x > *y) {
        tmp = *x;
        *x = *y;
        *y = tmp;
    }
}


void rank3(int *x, int *y, int *z)
{
    rank2(x, y);
    rank2(y, z);
    rank2(x, z);
}


int main()
{
    int i, j, k;

    printf("Enter i: ");
    scanf("%d", &i);

    printf("Enter j: ");
    scanf("%d", &j);

    printf("Enter k: ");
    scanf("%d", &k);

    rank3(&i, &j, &k);

    printf("After processing:\ni = %d, j = %d, k = %d\n", i, j, k);
    return 0;
}
