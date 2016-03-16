#include "10_2_libctree.h"

// В противовес 10_2 программе, пусть вместо константы будет define
#define BUFFER_SIZE 1000
#define LETTER "abcdefghijklmnopqrstuvwxyz"

/*
    Получаем новое слово со стандартного потока ввода и возращаем указатель на созданную строку.
    Под словом здесь понимается только набор символов, состоящий из англ. алфавита.
*/
char* get_word(void)
{
    int length = 0;
    char word[BUFFER_SIZE];
    char *new_word, symbol;

    while ( 1 ) {
        symbol = getchar();

        if ( strchr(LETTER, symbol) != NULL ) {
            word[length++] = symbol;

            if (length == (BUFFER_SIZE - 1)) {
                break;
            }

            continue;
        }

        if (length == 0) {
            if (symbol != '!') {
                continue;
            } else {
                return NULL;
            }
        }
        break;
    }

    word[length] = '\0';
    new_word = (char *) malloc(length * sizeof(char));

    if (new_word == NULL) {
        return NULL;
    }

    strcpy(new_word, word);
    return new_word;
}

// Создаём новый узел дерева. Содержимое узла заполняем введённым заранее словом.
struct Node* create_node(char *new_word)
{
    if (new_word == NULL) {
        return NULL;
    }

    struct Node *new_node = (struct Node *) malloc( sizeof(struct Node) );
    if (new_node == NULL) {
        return NULL;
    }

    new_node->left      = new_node->right = NULL;
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
void add_word_recursively(struct Node *tree, char* word)
{
    if (tree == NULL) {
        return;
    }

    int comparator;
    comparator = strcmp(word, tree->word);

    if (comparator == 0) {
        // новое слово и слово, хранимое в дереве - совпадают. Увеличиваем счётчик.
        tree->counter++;
        free(word);
        return;
    }

    if (comparator < 0) {
        // длина нового слова меньше длины слова текущего узла. В этом случае, добавляем слово в левую ветвь текущего узла.

        if (tree->left == NULL){
            // левого узла не существует, создаём новый
            tree->left = create_node(word);
            return;
        } else {
            // продолжаем обход по левой ветки в поиске совпадения
            add_word_recursively(tree->left, word);
        }
    } else {
        // длина нового слова больше длины слова в текущем узле. Добавляем слово в правую ветвь.

        if (tree->right == NULL){
            tree->right = create_node(word);
            return;
        } else {
            add_word_recursively(tree->right, word);
        }
    }
}

// Печатаем содержимое узлов
void print_tree_recursively(struct Node *tree)
{
    if (tree == NULL) {
        return;
    }

    print_tree_recursively(tree->left);
    printf("%s - %d\n", tree->word, tree->counter);
    print_tree_recursively(tree->right);
}

// Отчищаем все ресурсы, выделенные под дерево
void clear_tree_recursively(struct Node *tree)
{
    if (tree == NULL) {
        return;
    }

    struct Node *right_p;

    clear_tree_recursively(tree->left);
    right_p = tree->right;

    free(tree->word);
    free(tree);

    clear_tree_recursively(right_p);
}
