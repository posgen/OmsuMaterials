/*
    Определить, сколько раз каждое слово встречается во входном потоке.
    Вывести на экран в алфавитном порядке список слов с указанием их количества.

    Использовать для обработки двоичное дерево и реализовать рекурсивный алгоритм вставки слова в дерево.

    *Отличие от пособия*:
        -> функции для работы с деревом выделены в отдельную библиотеку
        -> при вводе слов используется знак вопроса для остановки

    Как компилировать - смортреть в первом примере из пособия (директория "10_1")
*/

#include <stdio.h>
#include "10_2_libctree.h"


int main()
{
    struct Node *root = NULL;
    char *new_word;

    puts("Enter words to collect (sign '!' to stop)");

    while ( 1 ) {
        new_word = get_word();
        if (new_word == NULL) {
            break;
        }

        if (root == NULL) {
            root = create_node(new_word);
        } else {
            add_word_recursively(root, new_word);
        }
    }

    print_tree_recursively(root);
    clear_tree_recursively(root);

    return 0;
}
