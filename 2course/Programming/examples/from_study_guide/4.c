/*
    Ввести предложение, оканчивающееся точкой, слова в котором отделены пробелом.
    Напечатать последнее слово из предложения. Строка имеет длину до 80 символов.
*/
#include <stdio.h>
#include <string.h> // библиотека для функций обработки строк
#include <locale.h> // установка русской локали (нужна для ОС Windows)

#define MAX_LENGTH 80

int main()
{
    setlocale(LC_ALL, "RUS");

    // current_sym - текущий введённый символ, previous_sym - предыдущий введённый символ
    char current_sym, previous_sym;
    char word[MAX_LENGTH];
    int index, word_index;

    printf("Введите предложение:\n");

    for (index = 0, current_sym = ' ', word_index = 0; index < MAX_LENGTH; index++) {
        previous_sym = current_sym;
        current_sym = getchar();

        if (current_sym == ' ')
            continue;
        if (current_sym == '.')
            break;

        if (previous_sym == ' ')
            word_index = 0;

        word[word_index++] = current_sym;
    }
    word[word_index] = '\0'; // устанавливаем конец строки

    if (strlen(word) == 0)
        printf("Что-то пошло не так");
    else
        printf("Последнее слово: %s", word);


    return 0;
}
