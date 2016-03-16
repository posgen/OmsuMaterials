#ifndef LIBCTREE_10_2
#define LIBCTREE_10_2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int counter;
    char *word;

    struct Node *left, *right;
};

char* get_word(void);
struct Node* create_node(char *head);
void add_word_recursively(struct Node *tree, char *word);
void print_tree_recursively(struct Node *tree);
void clear_tree_recursively(struct Node *tree);

#endif
