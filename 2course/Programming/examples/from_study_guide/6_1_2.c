/*
    Переставить элементы в массиве в обратном порядке с использованием указателей.
    Способ 2.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h> // установка русской локали (нужна для ОС Windows)

#define SIZE 80

void printText(char array[], int size)
{
    int i;
    for (i = 0; i < size; i++) {
        printf("%c ", array[i]);
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");

    char text[SIZE], sym;
    char *head, *tail;
    int i;

    srand(time(NULL));

    for (i = 0; i < SIZE ; i++) {
        text[i] = 97 + (rand() % 25);
    }

    printf("Исходный массив символов:\n");
    printText(text, SIZE);

    for (head = text, tail = &text[SIZE - 1]; head < tail;) {
        sym = *head;
        *head++ = *tail;
        *tail-- = sym;
    }

    printf("В обратном порядке:\n");
    printText(text, SIZE);
    return 0;
}

