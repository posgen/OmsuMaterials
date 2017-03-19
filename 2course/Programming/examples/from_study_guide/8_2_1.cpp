/*
    Скопировать один файл в другой. Имена файлов передаются из командной строки.

    Пример использования:
        8_2.exe source_file1.txt file2.txt
*/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <clocale>

using namespace std;

void error(const char *s, const char *s2 = "")
{
    cerr << s << " " << s2 << endl;
    exit(1);
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "RUS");

    if ( argc != 3 )
        error("Неправильное число аргументов. Использование: <название_программы>.exe <исходный_файл> <файл_для_записи>");

    ifstream source(argv[1]);
    if ( !source )
        error("Проблемы при открытии исходного файла", argv[1]);

    ofstream target(argv[2]);
    if ( !target )
        error("Проблемы при открытии файла для записи", argv[2]);

    char symbol;
    while ( source.get(symbol) )
        target.put(symbol);

    if ( !source.eof() || target.bad() )
        error("Возникли ошибки при копировании!");

    source.close();
    target.close();

    return 0;
}
