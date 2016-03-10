/*
    Пример форматированного вывода в файл.

    Для операций ввода вывода в С++, также как и в С, существет
    достаточно много возможностей для настройки ввода/вывода различных данных.
    Управляется всё это с помощью флагов, определённых как константы в ios_base.
    Основными являются:

    ios_base::boolalpha  - поток ввода или вывода преобразует данные типа bool в строки "true" и "false"
    ios_base::showbase   - при записи в поток вывода целые числа выводятся с основанием в качестве префикса (например, "Ox" - при выводе в шестнадцатиричном формате)
    ios_base::showpoint  - при записи в поток вывода числа с плавающей точкой всегда печатаются с этой самой точкой (ака "34.")
    ios_base::showpos    - при записи в поток вывода неотрицательные числа печатаются со знаком "+" в качестве префикса
    ios_base::skipws     - при вводе данных пропустить все пробельные символы до первого не пробельного символа
    ios_base::unitbuf    - при вводе данных заменить строчные буквы на заглавные. Возможно, работает по умолчанию только для английского алфавита

    ios_base::dec        - поток ввода/вывода при работе с 10 числами преобразует их к десятичному формату
    ios_base::hex        - ... к шестнадцатитеричному формату
    ios_base::oct        - ... к восмеричному формату

    ios_base::fixed      - при записи в поток вывода числа с плавающей точкой записываются в форме с фиксированной запятой (fixed-point notation)
    ios_base::scientific - при записи в поток вывода числа с плавающей точкой записываются в экспонециальной форме.

    ios_base::internal   - вывод любого значения форматируется к заданной ширине (width параметр) с помощью вставки специального символа (по умолчанию - пробел) начиная с некоторой внутренней позиции
    ios_base::left       - вывод значения форматируется к заданной ширине путём вставки специального символа после вывода данных (если ширина значения больше width, ни одного символа-заполнителя не вставляется)
    ios_base::right      - см. выше, но сначало идут спец. символы, а затем - вывод значения.

    Данные флаги могут комбинироваться с помощью оператора логического или - |
    Также существуют 3 заранее определённый комбинации флагов:

    ios_base::adjustfield - ios_base::left | ios_base::right | ios_base::internal
    ios_base::basefield   - ios_base::dec | ios_base::oct | ios_base::hex
    ios_base::floatfield  - ios_base::scientific | ios_base::fixed

    Для потоков ввода/вывода для работы с флагами определены следующие функции:

    cout.flags();       // возращает комбинацию текущих установленных флагов для потока.
                        // Возращаемое значение - специального типа ios_base::fmtflags
    cout.flags(flags);  // в качестве аргумента принимает любую комбинацию из флагов выше
    cout.setf(flags);   // Используется для установки группы флагов: boolalpha, showbase, showpoint, showpos, skipws.

    cout.setf(flags, mask) // в качестве mask используются одна из комбинаций: adjustfield, basefield, floatfield
                           // а в качестве flags - одно из соответсвующих маске значения.
                           // Применяется для выбора одного конкретного значения из опеределёных в маске.
*/
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    cout.setf(ios_base::hex, ios_base::basefield );  // установить hex-формат в качестве basefield
    cout.setf(ios_base::showbase );                  // показывать основание
    cout << 100 << " ::: " << 888.88 << endl;
    cout.unsetf ( ios_base::showbase );                // не показывать основание showbase
    cout << 100 << " ::: " << 888 << endl;

    // Использование fmtflags в качестве переменной для setf:
    ios_base::fmtflags ff;
    ff = cout.flags();
    ff &= ~ios_base::basefield;   // исключить basefield флаг
    ff |= ios_base::hex;          // установить шестнадцатиричный формат
    ff |= ios_base::showbase;     // установить showbase флаг
    cout.flags(ff);
    cout << 100 << '\n';

    // Демонстация флага boolalpha, когда и вывод, и ввод воспринимает true / false как bool значения
    cout.setf(ios_base::boolalpha);
    cin.setf(ios_base::boolalpha);
    bool truth;
    cout << "Enter true or false: ";
    cin >> truth;
    cout << "You choose: " << truth << endl;

    cout.unsetf(ios_base::boolalpha | ios_base::hex);
    cout << "True again: " << true << ", false: " << false << endl;

    cout.setf(ios_base::fixed);
    cout << "Float number in fixed notation: " << 4.56766 << endl;

    cout.unsetf(ios_base::fixed);
    cout.setf(ios_base::scientific);
    cout << "Float number in scientific notation: " << 4.56766 << endl;

    cout.unsetf(ios_base::scientific);

    cout << 4 << endl;
    cout.width(10);
    cout << 4 << endl;

    // после установки произвольного символа-заполнителя, необходим вызов функции width
    cout.fill('&');
    cout.width(10);
    cout << 4 << endl;

    // в следующей операции вывода значение из предыдущего вызова fill уже не используется.
    cout.setf(ios_base::left);
    cout << 4 << endl;

    // наконец, можно установить точность для вывода действительных чисел
    cout << 4.575868858 << endl;
    cout.precision(3); // точность в 2 цифры после запятой (точка - учитывается при установке)
    cout << 4.575868858 << endl;
    cout << 3.994566 << endl;


    // и пример с файловым выводом
    ofstream out_file("out_file.txt");
    out_file.precision(5);
    out_file << 4.575868858 << endl;

    out_file.setf(ios_base::showpos);
    out_file << 88 << endl;
    out_file << -18 << endl;
    out_file.unsetf(ios_base::showpos);

    out_file.setf(ios_base::boolalpha);
    out_file << true << endl;
    out_file << false << endl;

    out_file.close();

    return 0;
}
