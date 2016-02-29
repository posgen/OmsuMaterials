#ifndef LIBTREE_10_2
#define LIBTREE_10_2

#include <iostream>
#include <cstring>

struct Node {
    int counter;
    char *word;

    Node *left, *right;
};

char* get_word();
Node* create_node(char*);
void add_word_recursively(Node*, char* word);
void print_tree_recursively(Node*);
void clear_tree_recursively(Node*);

#endif
