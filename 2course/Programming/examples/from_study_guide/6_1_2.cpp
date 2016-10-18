/*
    Переставить элементы в массиве в обратном порядке с использованием указателей.
    Способ 2. Версия C++, стандарт: C++11
*/
#include <iostream>
#include <chrono>   // C++ библиотека для работы со временем
#include <random>  // ГПСЧ
#include <clocale> // установка русской локали (нужна для ОС Windows)

const size_t SIZE = 80;

void printText(char arr[], int arr_sz)
{
    for (size_t i = 0; i < arr_sz; i++) {
        std::cout << arr[i] << ' ';
    }
}

int main()
{
    std::setlocale(LC_ALL, "RUS");

    // Задаём зерно генератора
    unsigned long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    // Создаём генератор псевдо-случайных чисел
    std::mt19937_64 rnd_gener{ seed };

    // Случайное задание массива символов
    char text[SIZE];
    for (size_t i = 0; i < SIZE; ++i) {
        text[i] = 97 + ( rnd_gener() % 25 );
    }

    printf("Исходный массив символов:\n");
    printText(text, SIZE);

    char *head, *tail, sym;
    for (head = text, tail = &text[SIZE - 1]; head < tail;) {
        sym = *head;
        *head++ = *tail;
        *tail-- = sym;
    }

    printf("В обратном порядке:\n");
    printText(text, SIZE);

    return 0;
}

