/*
    Пример сохранения набора структур в файл и чтения произвольной структуры из него.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t NAME_SIZE = 250;

/*
    Структура не должна содержать указателей - при побайтовой записи структуры может 
    быть сохранён только адрес на который указывает указатель!
*/
typedef struct {
    char         name[NAME_SIZE];
    double       price;
    unsigned int count;
} Product;

int main()
{
    char file_name[] = "products.bin", buf[NAME_SIZE];
    size_t prods_count = 0;
    Product prd;

    // Поток вывода для записи в файл
    FILE *out_stream = fopen(file_name, "wb");

    if ( out_stream != NULL ) {
        printf("Products (введите пустое имя для остановки)\n");

        // Вводим экземпляры структур, пока не надоест
        while ( true ) {
            printf("  название: ");
            fgets(prd.name, NAME_SIZE, stdin);

            if ( strlen(prd.name) == 0 ) {
                break;
            }

            printf("  цена: ");
            /*
                Для корректной работы fgets и fscanf надо помнить об правилах ввода
                символов. Поэтому все три поля вводятся fgets (построчно), а затем
                цифры разбираются через atof/ atoi.
            */
            fgets(buf, NAME_SIZE, stdin);
            prd.price = atof(buf);

            printf("  количество: ";
            fgets(buf, NAME_SIZE, stdin);
            prd.count = atoi(buf);

            /*
                Осуществляем запись в файл.
                Функция write ожидает в качестве первого аргумента указатель на начало блока
                для записи.

                Таким образом, мы берём адрес переменной структуры (фактически - указатель на начало блока памяти,
                где лежит структура), указываем сколько байт занимает каждый элемент (размер структуры -
                sizeof(Product)) и количество элементов для записи (1, в данном случае).

                Запись структур идёт последовательно.
            */
            fwrite(&prd, sizeof(Product), 1, out_stream);
            prods_count++;
        }
        fclose(out_stream);

        Product prd2; // другая переменная нашей структуры. Используется для загрузки структуры из файла.
        size_t prod_number = 0;

        //открываем файл для чтения
        FILE *in_stream = fopen(file_name, "rb");

        if ( in_stream ) {
            printf("Было сохранено %lu продуктов. Введите номер для загрузки конкретного\n", prods_count);

            // ждём, пока будет введён корректный номер, соответствующий количеству введённых структур
            while ( prod_number < 1 || prod_number > prods_count ) {
                fscanf("%lu", &prod_number);
            }

            /*
                Функция fseek - устанавливает позицию во входном потоке (поток, открытый на чтение),
                с которой начнётся чтение данных.

                Первая структура имеет отсуп равный нулю, поэтому от введённого номера отнимается 1.
            */
            fseek(in_stream, (prod_number - 1) * sizeof(Product), SEEK_SET);

            /*
                Читаем данные из потока в структуру. Используется тот же трюк, что и при созранении:
                    есть переменная prd2, под которую выделён блок в памяти. Размер этого блока равен сумме размеров
                    всех полей структуры. Функция fread получает указатель на начало этого блока - &prd2 -
                    и затем побайтого заполняет его данными из потока. Из потока считываются sizeof(prd2) байт 1 раз.
            */
            fread(&prd2, sizeof(Product), 1, in_stream);
            fclose(in_stream);

            printf("Был загружен продукт:\n");
            printf("  Название: %s\n    цена: %f\n    количество: %lu\n", prd2.name, prd2.price, prd2.count);
        }
    }
    return 0;
}

