#include <stdio.h>
#include <stdlib.h>

// Убрать комментарий при необходимости!
//#include <windows.h>

int nod(int first, int second)
{
    if ( second == 0 ) {
        return 0;
    }

    int r = first % second;

    while ( r != 0 ) {
        first = second;
        second = r;
        r = first % second;
    }

    return abs( second );
}

int main()
{
    // Убрать комментарии при необходимости!
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);

    int number1, number2;
    printf("Введите два целых числа: ");
    scanf("%d %d", &number1, &number2);

    int result = nod(number1, number2);
    printf("НОД от %d и %d равен %d\n", number1, number2, result);

    return 0;
}
