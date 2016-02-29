/*
    Пример перезаписи в выходном потоке.
    Оригинал тут: http://www.cplusplus.com/reference/ostream/ostream/seekp/
*/

#include <iostream>
#include <fstream>

using namespace std;

int main () {
    /*
        Здесь показано, как можно отложить открытие файла. Переменная потока сначало определяется,
        а затем конкретный файл открывается через функцию экземпляра - open.
    */
    ofstream out_file;
    out_file.open("example_rewriting.txt");

    if (out_file) {
        out_file.write ("This is an apple",16);
        long pos = out_file.tellp();
        out_file.seekp (pos-7);
        out_file.write (" sam",4);

        out_file.close();
        // В итоге в файле окажется строка: "This is a sample"

        cout << "Writing complete";
    } else {
        cout << "Error with opening file" << endl;
    }

    return 0;
}
