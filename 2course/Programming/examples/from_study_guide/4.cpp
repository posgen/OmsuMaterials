/*
    Ввести предложение, оканчивающееся точкой, слова в котором отделены пробелом.
    Напечатать последнее слово из предложения. Строка имеет длину до 80 символов.

    Версия для С++
*/
#include <iostream>
#include <clocale>
#include <cstring>

const int MAX_LENGTH = 80;

int main()
{
    std::setlocale(LC_ALL, "RUS");

    // current_sym - текущий введённый символ, previous_sym - предыдущий введённый символ
    char current_sym, previous_sym;
    char word[MAX_LENGTH];
    int index, word_index;

    std::cout << "Введите предложение (точка - означает конец):\n";

    for (index = 0, current_sym = ' ', word_index = 0; index < MAX_LENGTH; index++) {
        previous_sym = current_sym;
        std::cin.get(current_sym);

        if (current_sym == ' ')
            continue;
        if (current_sym == '.')
            break;

        if (previous_sym == ' ')
            word_index = 0;

        word[word_index++] = current_sym;
    }
    word[word_index] = '\0'; // устанавливаем конец строки

    if (strlen(word) == 0) {
        std::cout << "Неправильный ввод";
    } else {
        std::cout << "Последнее слово: " << word;
    }


    return 0;
}
