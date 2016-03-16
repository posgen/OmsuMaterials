#include "10_2_libtree.h"

// В противовес 10_1 программе, пусть вместо константы будет define
#define BUFFER_SIZE 1000
#define LETTER "abcdefghijklmnopqrstuvwxyz"

/*
    Получаем новое слово со стандартного потока ввода и возращаем указатель на созданную строку.
    Под словом здесь понимается только набор символов, состоящий из англ. алфавита.
*/
char* get_word()
{
    /*
        Присваивание начального значения в современном C++ (C++11 и выше)
        Аналогично по смыслу:
            int len = 0;
            int len(0); // этот вариант больше не рекомендуется использовать
    */
    int length{0};
    char word[BUFFER_SIZE];
    char *new_word, symbol;

    while (true) {
        symbol = std::cin.get();

        if (strchr(LETTER, symbol) != nullptr) {
            word[length++] = symbol;

            if (length == (BUFFER_SIZE - 1)) {
                break;
            }

            continue;
        }

        if (length == 0) {
            if (symbol != '!')
                continue;
            else
                return nullptr;
        }
        break;
    }

    word[length] = '\0';
    new_word = new char[length];
    if (new_word == nullptr)
        return nullptr;

    std::strcpy(new_word, word);
    return new_word;
}

// Создаём новый узел дерева. Содержимое узла заполняем введённым заранее словом.
Node* create_node(char *new_word)
{
    if (new_word == nullptr) {
        return nullptr;
    }

    Node *new_node{new Node};
    if (new_node == nullptr)
        return nullptr;

    new_node->left      = new_node->right = nullptr;
    new_node->word      = new_word;
    new_node->counter   = 1;

    return new_node;
}

/*
    Добавляем слово в дерево. Здесь:
        tree - указатель на текущий узел дерева (обход начинается с корневого узела)
        word - указатель на слово, которое хотим добавить.
    Если слово уже присутствует в дереве, то просто увеличиваем его счётчик, а новый узел не создаём.
*/
void add_word_recursively(Node *tree, char* word)
{
    if (tree == nullptr)
        return;

    int comparator;
    comparator = std::strcmp(word, tree->word);

    if (comparator == 0) {
        // новое слово и слово, хранимое в дереве - совпадают. Увеличиваем счётчик.
        tree->counter++;
        delete[] word;
        return;
    }

    if (comparator < 0) {
        // длина нового слова меньше длины слова текущего узла. В этом случае, добавляем слово в левую ветвь текущего узла.

        if (tree->left == nullptr){
            // левого узла не существует, создаём новый
            tree->left = create_node(word);
            return;
        } else {
            // продолжаем обход по левой ветки в поиске совпадения
            add_word_recursively(tree->left, word);
        }
    } else {
        // длина нового слова больше длины слова в текущем узле. Добавляем слово в правую ветвь.

        if (tree->right == nullptr){
            tree->right = create_node(word);
            return;
        } else {
            add_word_recursively(tree->right, word);
        }
    }
}

// Печатаем содержимое узлов
void print_tree_recursively(Node* tree)
{
    if (tree == nullptr)
        return;

    print_tree_recursively(tree->left);
    std::cout << tree->word << " - " << tree->counter << std::endl;
    print_tree_recursively(tree->right);
}

// Отчищаем все ресурсы, выделенные под дерево
void clear_tree_recursively(Node *tree)
{
    if (tree == nullptr)
        return;

    Node *right_p;

    clear_tree_recursively(tree->left);
    right_p = tree->right;

    delete[] tree->word;
    delete tree;

    clear_tree_recursively(right_p);
}
