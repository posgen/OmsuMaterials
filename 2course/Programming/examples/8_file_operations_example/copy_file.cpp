/*
    Пример копирования файла через промежуточный буфер

*/
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    /*
        Класс ifstream используется для создания потока на чтение файла.
        Конструктор принимает два параметра:
            char * - имя файла
            mode   - флаги для открытия файла. Сами флаги являются отдельным типом, который сводится к целому значению.
                     Флаги комбинируются с помощью оператора | (исключающее или). Значение по умолчанию - std::ios_base::in

        Виды mode:
            std::ios_base::app      - добавление в конец файла
            std::ios_base::ate      - открыть и найти конец файла
            std::ios_base::binary   - режим чтение/запись в двоичном режиме (зависит от ОС)
            std::ios_base::in       - открытие потока на чтение
            std::ios_base::out      - открытие потока на запись
            std::ios_base::trunc    - при открытии потока установить длину файлав 0.

        Пример:
            ifstream in_file("some_file.dat", std::ios_base::in | std::ios_base::binary);
    */
    ifstream in_file("input.txt");

    if (in_file) {
        /*
        Класс ofstream используется для создания потока на запись в файл.
        */
        ofstream out_file("output.txt");

        /*
            Таким образом можно узнать размер файла.

            Метод seekg - устанавливает позицию для извлечения следующего символа для извлечения в потоке на чтение.
            Есть две формы:
                in_str.seekg(position) - устанавливает позицию относительно начала файла. position - целое число, количество байт для отступа.
                in_str.seekg(offset, start_point) - отступает offset байт (опять же, целое число) от некоторого отсчёта start_point.
                    start_point - одно из следующих значений:
                        ios_base::beg - начало потока
                        ios_base::cur - текущая позиция в потоке
                        ios_base::end - конец потока

            Ниже сначало позиция для извлечения символа сначало устанавливается в конец файла,
            затем метод tellg - возращает текущую позицию (фактически - количество байтов в потоке) и
            текущая позиция возращается в начало файла.

            Для выходного потока (ofstream, fstream) существуют аналогичные функции для перемещению по файлу - seekp / tellp.
            Они устанавливают позицию для записи следующего символа.
        */
        if (out_file.open()) {
            in_file.seekg (0, in_file.end);
            long size = in_file.tellg();
            in_file.seekg (0);

            // Буфер для считывания из файла
            char* buffer = new char[size];

            // Функция read считывает size байт в область, заданную указателем buffer
            in_file.read(buffer, size);

            // Функция write аналогична по аргументам read, разве что пишет из указанной области size байт в выходной поток
            out_file.write(buffer, size);

            delete[] buffer;

            out_file.close();
            in_file.close();

            cout << "Coping complete" << endl;
        } else {
            cerr << "Error with opening output file" << endl;
        }
    } else {
        cerr << "Error with opening file" << endl;
    }

    return 0;
}
