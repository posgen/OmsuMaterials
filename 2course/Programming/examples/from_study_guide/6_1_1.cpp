/*
    Переставить элементы в массиве в обратном порядке с использованием указателей.
    Используется символьный массив со случайно установленными элементами.
    Способ 1. Версия для C++ (стандарт C++11)
*/
#include <iostream>
#include <chrono>   // C++ библиотека для работы со временем
#include <random>  // ГПСЧ
#include <clocale> // установка русской локали (нужна для ОС Windows)

const size_t SIZE = 80;

void printText(char arr[], size_t arr_sz)
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

    std::cout << "Исходный массив символов:\n";
    printText(text, SIZE);

    char *head, *tail;
    char sym;
    // Перестановка элементов массива через указатели
    for (head = text, tail = &text[SIZE - 1]; head < tail; head++, tail--) {
        sym = *head;
        *head = *tail;
        *tail = sym;
    }

    std::cout << "Он же после перестановки:\n";
    printText(text, SIZE);

    return 0;
}
