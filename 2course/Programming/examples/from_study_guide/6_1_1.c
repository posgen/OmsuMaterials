/*
    Переставить элементы в массиве в обратном порядке с использованием указателей.
    Способ 1.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    char text[SIZE], sym;
    char *head, *tail;
    int i;

    srand(time(NULL));

    for (i = 0; i < SIZE ; i++) {
        text[i] = 97 + (rand() % 25);
    }

    printf("Initial text:\n");
    printText(text, SIZE);

    for (head = text, tail = &text[SIZE - 1]; head < tail; head++, tail--) {
        sym = *head;
        *head = *tail;
        *tail = sym;
    }

    printf("After inverting:\n");
    printText(text, SIZE);
    return 0;
}

