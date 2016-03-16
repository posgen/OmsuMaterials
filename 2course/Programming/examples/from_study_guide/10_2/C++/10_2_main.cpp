/*
    Определить, сколько раз каждое слово встречается во входном потоке.
    Вывести на экран в алфавитном порядке список слов с указанием их количества.

    Использовать для обработки двоичное дерево и реализовать рекурсивный алгоритм вставки слова в дерево.

    *Отличие от пособия*:
        -> используется C++ вместо C
        -> функции для работы с деревом выделены в отдельную библиотеку

    Как компилировать - смортреть в первом примере из пособия (директория "10_1")
*/

#include <iostream>
#include "10_2_libtree.h"

using namespace std;

int main()
{
    Node *root{nullptr};
    char *new_word;

    cout << "Enter words to collect (sign '!' to stop)" << endl;

    while (true) {
        new_word = get_word();
        if (new_word == nullptr)
            break;

        if (root == nullptr) {
            root = create_node(new_word);
        } else {
            add_word_recursively(root, new_word);
        }
    }

    print_tree_recursively(root);
    clear_tree_recursively(root);

    return 0;
}
