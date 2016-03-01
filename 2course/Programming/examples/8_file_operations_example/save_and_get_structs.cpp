/*
    Пример созранения набора структур в файл и чтения произвольной структуры из него.
*/

#include <iostream>
#include <fstream>
#include <cstring>

#define NAME_SIZE 250

using namespace std;

// Структура не должна содержать указателей - при побайтовой записи структуры может быть сохранён только адрес
// на который указывает указатель!
struct Product {
    char         name[NAME_SIZE];
    double       price;
    unsigned int count;
};

int main()
{
    char file_name[] = "products.dat", buf[NAME_SIZE];
    size_t prods_count{0};
    Product prd;

    // Снова используем экземпляр класса ofstream для записи в файл.
    ofstream out_file(file_name, ios::binary | ios::out);

    if ( out_file ) {
        cout << "Products (enter empty name to stop)" << endl;

        // Вводим структуры, пока не надоест
        while ( true ) {
            cout << endl << "  name: ";
            cin.getline(prd.name, NAME_SIZE);

            if ( strlen(prd.name) == 0 ) {
                break;
            }

            cout << "  price: ";
            /*
                Для корректной работы нельзя использовать совметно
                функцию getline и оператор >>. Поэтому все три поля вводятся
                через getline, и цифры разбираются через atof/ atoi.
            */
            cin.getline(buf, NAME_SIZE);
            prd.price = atof(buf);

            cout << "  count: ";
            cin.getline(buf, NAME_SIZE);
            prd.count = atoi(buf);

            /*
                Осуществляем запись в файл.
                Функция write ожидает в качестве первого аргумента указатель типа char
                (поскольку фактически запись осуществляет побайтово).

                Таким образом, мы берём адрес переменной структуры (фактически - указатель на начало блока памяти,
                где лежит структура), приводим его к типу char*
                и указываем, какой сколько байт должено быть считано (sizeof(prd)) начиная с адреса, на который
                указывает первый аргумент.

                Запись структур идёт последовательно.
            */
            out_file.write( (char *) &prd, sizeof(prd) );
            prods_count++;
        }
        out_file.close();

        Product prd2; // другая переменная нашей структуры. Используется для загрузки структуры из файла.
        size_t prod_number{0};

        //открываем файл для чтения
        ifstream in_file(file_name, ios::binary | ios::in);

        if ( in_file ) {
            cout << "There were " << prods_count << " saved. Enter the number to load a product" << endl;

            // ждём, пока будет введён корректный номер, соответствующий количеству введённых структур
            while ( prod_number < 1 || prod_number > prods_count ) {
                cin >> prod_number;
            }

            /*
                Напоминаем, что функция seekg - устанавливает позицию во входном потоке (поток, открытый на чтение),
                с которой начнётся чтение данных.

                Первая структура имеет отсуп равный нулю, поэтому от введённого номера отнимается 1.
            */
            in_file.seekg( (prod_number - 1) * sizeof(Product) );

            /*
                Читаем данные из потока в структуру. Опять же, требуется явное приведение первого аргумента
                к типу char*. Используется тот же трюк, что и при созранении:
                    есть переменная prd2, под которую выделён блок в памяти. Размер этого блока равен сумме размеров
                    всех полей структуры. Функция read получает указатель на начало этого блока - (char *) &prd2 -
                    и затем побайтого заполняет его данными из потока. Из потока считываются sizeof(prd2) байт.
            */
            in_file.read( (char *) &prd2, sizeof(prd2) );
            in_file.close();

            cout << "You choose:" << endl;
            cout << prd2.name << " --- " << prd2.price << " --- " << prd2.count << endl;
        }
    }
    return 0;
}

