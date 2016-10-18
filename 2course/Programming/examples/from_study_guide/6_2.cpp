/*
    Ввести с клавиатуры в виде одной строки арифметическое выражение, включающее 2 положительных целых
    и знак одной из 4-х арифметических операций (+, -, *, /), размещённых между ними, и вычислить значение выражения.

    Версия С++ (но используются C-строки для демонстрации использования указателей)
*/
#include <iostream>
#include <cstdlib>  // функции преобразования строки в числа: atoi, atof, ...
#include <cstring>  // стандартная библиотека языка C для работы со строками
#include <clocale>  // установка русской локали (нужна для ОС Windows)

const size_t SIZE = 99;
const size_t OP_SIZE = 9;

int main()
{
    std::setlocale(LC_ALL, "RUS");

    char expression[SIZE];
    char op_left[OP_SIZE], op_right[OP_SIZE]; // левый и правый операнды выражения
    char operation, *beg;
    char numbers[] = "0123456789";
    int len, result, value_left, value_right;

    std::cout << "Введите арифметическое выражение (число, знак, число):\n";
    std::cin.getline(expression, SIZE);

    /*
        Функция strpbrk(const char *str1, const char *str2) возращает указатель на позицию
        в строке str1 первого вхождения любого символа из строки str2.

        Например, пусть дана строка "4depahnti4b3trde" и строка "aei".
            char str1[] = "4depahnti4b3trde", str2[] = "aei";
            char *pos; // указатель используется для запоминания позиции.
        При выполнении вызова:
            pos = strpbrk(str1, str2);
        указатель pos будет указывать на третий символ строки str1 (поскольку из символов 'a', 'e', 'i', буква 'e' - появляется
        раньше всех в исходной строке).
        То есть,
            pos == &str1[2]; // адреса указателя и третьего элемента совпадают.
           *pos == 'e'; // значение, на которое указывает указатель.

        Графически, можно представить так:
            // есть массив символов (строка в терминах языка C)
            ['4', 'd', 'e', 'p', 'a', 'h', 'n', 't', 'i', '4', 'b', '3', 't', 'r', 'd', 'e', '\0']
                        ^
                        |
                        p
            // p указывает на третий символ исходной строки

        Если мы хотим продолжить поиск в строке символов 'a', 'e', или 'i', то это можно сделать, используя полученный указатель p:
            // здесь p + 1 - указывает на 4-ый элемент исходной строки
            // и вызов этой функции эквивалентен такому: strpbrk("pahnti4b3trde", "aei")
            pos = strpbrk(p + 1, str2);
        После второго вызова, указатель pos будет указыват на 5-ый элемент в строке str1
            ['4', 'd', 'e', 'p', 'a', 'h', 'n', 't', 'i', '4', 'b', '3', 't', 'r', 'd', 'e', '\0']
                                  ^
                                  |
                                  p

        Ниже данная функция используется для того, чтобы найти первую цифру во введённой пользователем строке.
    */
    beg = std::strpbrk(expression, numbers);

    /*
        Функция strspn(const char *str1, const char *str2 ); возращает количество символов из строки str2,
        которые находятся последовательно в строке str1. Как только встречается первый символ в строке str1,
        который не входит в строку str2 - поиск прекращается и возращается результат. Например,
            int count;
            char strtext[] = "129th";
            char cset[] = "1234567890";
            count = strspn(strtext, cset);
        Выше переменная count будет равна 3 (три цифры идут подряд в исходной строке).

            int count;
            char strtext[] = "129th4455";
            char cset[] = "1234567890";
            count = strspn(strtext, cset);
        Тут опять переменная count равна трём, потому что после цифры '9' идёт буква, не входящяя в строку cset.

            int count;
            char strtext[] = "a129th";
            char cset[] = "1234567890";
            count = strspn(strtext, cset);
        Тут переменная count равна нулю, поскольку первый же символ строки strtext не является символом из строки cset
    */
    len = std::strspn(beg, numbers);
    std::strncpy(op_left, beg, len);
    op_left[len] = '\0';
    value_left = std::atoi(op_left);

    beg = std::strpbrk(beg, "+-*/");
    operation = *beg;

    beg = std::strpbrk(beg, numbers);
    len = std::strspn(beg, numbers);
    std::strncpy(op_right, beg, len);
    op_right[len] = '\0';
    value_right = std::atoi(op_right);

    switch(operation) {
        case '+':
            result = value_left + value_right;
            break;
        case '-':
            result = value_left - value_right;
            break;
        case '*':
            result = value_left * value_right;
            break;

        case '/':
            if (value_right != 0)
                result = value_left / value_right;
            else {
                std::cout << "Ошибка! Деление на нуль\n";
                return 1;
            }
            break;
        default:
            std::cout << "Неизвестная операция\n";
            return 1;
    }

    std::cout << "Введённое выражение:\n" << op_left << ' '
                                          << operation << ' '
                                          << op_right << " = "
                                          << result << '\n';

    return 0;
}
