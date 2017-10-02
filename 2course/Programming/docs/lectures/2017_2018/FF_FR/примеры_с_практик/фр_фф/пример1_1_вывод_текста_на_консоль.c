#include <stdio.h>
#include <stdlib.h>

// Убрать комментарий при необходимости!
//#include <windows.h>

void draw_animal(const int choise)
{
    switch ( choise ) {
    case 1:
        printf("\n\n\nThe cat\n");
        printf(
               "?[e_9]?\n"
               "      (())!\n"
               "      2  2\n"
        );
        break;

    case 2:
        printf("\nThe dog\n");
        printf(
               "!(0_0)!\n"
               "      [ ]?\n"
               "      _ _\n"
               "     _   _\n"
        );
        break;


    default:
        printf("\nUnknown animal\n");
        printf(
               "(*_*)\n"
               "   []\n"
               "   _ _\n"
        );
    }
}

int main()
{
    // Убрать комментарии при необходимости!
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);

    int my_choise;
    printf("Введите единицу для показа кота, двойку - собаки: ");
    scanf("%d", &my_choise);

    draw_animal( my_choise );

    return 0;
}
