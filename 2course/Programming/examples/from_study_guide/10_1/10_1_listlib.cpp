#include "10_1_listlib.h"


namespace listlib {
    // Предполагаем, что человеку будет лень вводить больше 1000 символов
    const int BUFFER_SIZE = 1000;

    char* get_line()
    {
        int len;
        char buffer[BUFFER_SIZE], *p_str;

        std::cin.getline(buffer, BUFFER_SIZE);
        len = std::strlen(buffer);

        if (len == 0) {
            /*
                nullptr - ключевое слове в C++, означающее нулевой (пустой, неинициализированный) указатель.
                В С для этого использовали макрос NULL.
            */
            return nullptr;
        }

        // Из глубин памяти помним, что strlen возращает число символов без учёта символа конца строки '\0'
        p_str = new char[len + 1];
        if ( p_str == nullptr )
            return nullptr;

        std::strcpy(p_str, buffer);
        return p_str;
    }

    Cell* create_cell()
    {
        Cell *item;
        char *str;

        str = get_line();
        if (str == nullptr)
            return nullptr;

        item = new Cell;
        if (item == nullptr)
            return nullptr;

        item->p_str = str;
        item->length = strlen(str);

        return item;
    }

    /*
        Добавляем элемент с список.
            head -> указатель на первый узел
            new_item -> указатель на новый узел, который добавляется к списку

        В данном случае при добавлении узла происходит упорядочивание по длине строки, которую содержит каждый элемент.
        Чем больше длина строки элемента, тем дальше в список он будет помещён.
    */
    Cell* insert_to_list(Cell *head, Cell *new_item)
    {
        Cell *current = head, *previous = nullptr;

        while (true) {
            if (current == nullptr) {
                if (previous == nullptr) {
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

                if (previous == nullptr) {
                    return new_item;
                }

                previous->next = new_item;
                return head;
            }
        }
    }

    void print_list(Cell *head)
    {
        Cell *pointer = head;

        while (pointer != nullptr) {
            std::cout << pointer->p_str << std::endl;
            pointer = pointer->next;
        }
    }

    void clear_list(Cell *head)
    {
        Cell *curr_p = head, *next_p = curr_p->next;

        do {
            delete[] curr_p->p_str;
            delete curr_p;

            curr_p = next_p;
            next_p = curr_p->next;
        } while (next_p != nullptr);
    }
}

