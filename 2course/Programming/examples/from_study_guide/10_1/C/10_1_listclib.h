/*
    Ниже используемые директивы препроцессора нужны для того, чтобы
    гарантировать то, что функции/переменные/структуры/классы из конкретной
    библиотеки будут объявлены только один раз. Здесь:
        #ifndef LISTCLIB_10_1 - проверяет, не было ли объявления идентификатора "LISTCLIB_10_1"

        #define LISTCLIB_10_1 - объявлем идентификатор "LISTCLIB_10_1"

        #endif - закрытие директивы "#ifndef"

*/
#ifndef LISTCLIB_10_1
#define LISTCLIB_10_1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Cell {
    char *p_str;
    int length;
    /*
        Объявляется указатель на структуру своего же типа.
        В C при объявлении переменных и указателей типа структуры нужно указывать ключевое слово *struct*:
            struct Cell *next;
    */
    struct Cell *next;
};

// Одно отличие по сравнению с пособием: в C++ не надо явно указывать void для функции,
// которая не принимает никаких аргументов.
struct Cell* create_cell();
struct Cell* insert_to_list(struct Cell*, struct Cell*);

// И не забываем, что при объявлении функции имя переменной аргумента указывать не обязательно
void print_list(struct Cell*);
void clear_list(struct Cell*);


#endif

