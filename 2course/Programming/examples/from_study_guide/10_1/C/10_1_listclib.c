#include "10_1_listclib.h"

// Предполагаем, что человеку будет лень вводить больше 1000 символов
static const int BUF_SIZE = 1000;

// Функция считывания строки из консольного ввода и динамического создания массива под её хранение.
char* get_line()
{
    int len;
    char buffer[BUF_SIZE], *p_str;

    /*
        fgets - более безопасное чтение строки, чем функция gets
            fgets(char *str, int size, FILE *stream);

        fgets принимает три аргумента:
            1) str - указатель типа char* на массив символов
            2) size - максимальный размер считываемых элементов (в массив char* заносится (size - 1) символ)
            3) stream - указатель на поток ввода. В данном случае, stdin - это указатель типа FILE на стандартный консольный входной поток.

        Функция прекращает запись в массив символов, если будет считан size - 1 символ, или встретится символ новой строки - '\n'
        Символ конца строки - '\0' - подставляется последним символом, после прекращения записи.

        Очень неприятная особенность данной функции состоит в том, что если найден символ новой строки
        до того, как считались size - 1 символов, '\n' - будет помещён в массив str.
    */
    fgets(buffer, BUF_SIZE, stdin);
    len = strlen(buffer);

    if (len == 1 && buffer[0] == '\n') {
        // '\n' - данный символ не равен символу пустой строки, поэтому strlen возращает единицу.
        // условие в if означает, что был нажат только Enter, то есть введена пустая строка.
        // на этом ввод строк заканчиваем.
        // В С макрос NULL используется для обозначения нулевого указателя (неинициализированного, или пустого).
        return NULL;
    }
    buffer[len - 1] = '\0'; // выгоняем символ '\n' из введённой строки

    // Из глубин памяти помним, что strlen возращает число символов без учёта символа конца строки '\0'
    // Память выделяется под len элементов, потому что выше на один символ ('\n') строка была сокращена.
    p_str = (char *) malloc( len * sizeof(char) );
    if ( p_str == NULL ) {
        return NULL;
    }

    strcpy(p_str, buffer);
    return p_str;
}

// Функция создания нового элемента списка
struct Cell* create_cell()
{
    struct Cell *item;
    char *str;

    str = get_line();
    if (str == NULL) {
        return NULL;
    }

    item = (struct Cell *) malloc( sizeof(struct Cell) );
    if (item == NULL) {
        return NULL;
    }

    item->p_str = str;
    item->length = strlen(str);

    return item;
}

/*
    Добавляем элемент в список.
        head -> указатель на первый узел
        new_item -> указатель на новый узел, который добавляется к списку

    В данном случае при добавлении узла происходит упорядочивание по длине строки, которую содержит каждый элемент.
    Чем больше длина строки элемента, тем дальше в список он будет помещён.
*/
struct Cell* insert_to_list(struct Cell *head, struct Cell *new_item)
{
    struct Cell *current = head, *previous = NULL;

    // Вот так-то, в С нет булева типа :)
    while ( 1 ) {
        if (current == NULL) {
            if (previous == NULL) {
                return new_item;
            }

            previous->next = new_item;
            return head;
        }

        if (new_item->length > current->length) {
            previous = current;
            current = current->next;
        } else {
            new_item->next = current;

            if (previous == NULL) {
                return new_item;
            }

            previous->next = new_item;
            return head;
        }
    }
}

// Печать всех значений элементов списка
void print_list(struct Cell *head)
{
    struct Cell *pointer = head;

    while (pointer != NULL) {
        // Функция puts - печатает строки и вставляет символ '\n' в конце
        // Её можно использовать с массивами типа char только тогда, когда вы уверенны в том,
        // что в вашем массиве присутствует символ конца строки - '\0' !!!
        puts(pointer->p_str);
        pointer = pointer->next;
    }
}

// Последовательное удаление динамического списка из памяти
void clear_list(struct Cell *head)
{
    struct Cell *curr_p = head, *next_p = curr_p->next;

    do {
        free(curr_p->p_str);
        free(curr_p);

        curr_p = next_p;
        next_p = curr_p->next;
    } while (next_p != NULL);
}
