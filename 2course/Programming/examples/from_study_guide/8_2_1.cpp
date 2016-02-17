/*
    Скопировать один файл в другой. Имена файлов передаются из командной строки.

    Пример использования:
        8_2.exe source_file1.txt file2.txt
*/
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

void error(const char *s, const char *s2 = "")
{
    cerr << s << " " << s2 << endl;
    exit(1);
}

int main(int argc, char *argv[])
{
    if ( argc != 3 )
        error("Wrong number of arguments");

    ifstream source(argv[1]);
    if ( !source )
        error("Can't open source file", argv[1]);

    ofstream target(argv[2]);
    if ( !target )
        error("Can't open source file", argv[2]);

    char symbol;
    while ( source.get(symbol) )
        target.put(symbol);

    if ( !source.eof() || target.bad() )
        error("There were errors during copying");

    source.close();
    target.close();

    return 0;
}
