/*
    Скопировать один файл в другой. Имена файлов передаются из командной строки.
    Пример использования низкоуровневых функций ввода-вывода.

    Пример использования:
        8_2_2.exe source_file1.txt file2.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    // Дескрипторы входного и выходного файлов.
    int source_file_descriptor, target_file_descriptor;
    // Количество прочитанных байт.
    int n;
    char buf[BUFSIZ];

    if ( argc != 3 ) {
        perror("Wrong number of arguments");
        return -1;
    }

    if ( (source_file_descriptor = open(argv[1], O_RDONLY)) == -1 ) {
        perror(argv[1]);
        return -1;
    }

    // Третий параметр в функции open определяет права доступа к создаваемому файлу в UNIX-системах
    if ( (target_file_descriptor = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR)) == -1 ) {
        perror(argv[2]);
        return -1;
    }

    while ( (n = read(source_file_descriptor, buf, BUFSIZ)) > 0 )
        write(target_file_descriptor, buf, n);

    close(source_file_descriptor);
    close(target_file_descriptor);

    return 0;
}
