/*
    !Все файлы с номерами меньше текущего в одной директории - обязательны к прочтению в порядке возрастания номеров!

    В C++ все простые типы данных (int, double, char) участвуют в некоторых выражениях. В этих выражениях
    вычисления осуществляются с помощью операторов - специальных символьных идентификаторов, обозначающих,
    как ни странно, некоторую операцию. Как пример операторов - обычные арифметические операции: +, -, *, /.
        int num1 = 45, num2 = 4, num3 = 8;
        num3 += num1 + num2 * 3 - num2 / num1; //  тут всё очевидно
             ^
             |
          это тоже оператор

    Можно вспомнить об логических операторах - && (логическое и), || (логическое или), !(отрицание) -
    используемые в if-выражениях или циклах. И операции выделения динамической памяти - new и delete также
    являются операторами.

    Так вот, для любого класса можно переопределить практически любые операторы (исключения составляют следующие штуки,
    чтобы они не означали: "::  . .* sizeof typeid alignof"). Определение операторов для конкретного класса
    называется их перегрузкой.

    В общем виде, перегрузка любого оператора заключается в определении специальной функции, имя которой
    начинается с ключевого слова operator, за которым следует знак оператора. Например:
        operator+
        operator+=
    Также как и у обычных функций, у операторов имеются возращаемое значение и аргументы.

    Некоторая сложность с перегрузкой операторов состоит в том, что C++ позволяет опеределять 2-мя способами:
        1) В виде методов класса
        2) В виде дружественных классу функций

    Рассмотрим на примере написания класса, представляющего собой комплексное число (используется способ 1)):
        class Complex
        {
            double re, im; // комплексное число имеет действительную и мнимую часть, которые являются действительными числами
        public:

            Complex(double _re, double _im) : re{_re}, im{_im}
            {} // простой констуктор

            // пара методов, доступ к текущим значениям целой и действительной части:
            double get_re()
            {
                return re;
            }

            double get_im()
            {
                return im;
            }

            // Перегрузка оператора +. Позволяет делать вот так:
            // Complex z1(1, 2), z2(3.4, 5.5);
            // Complex z3 = z1 + z2;
            Complex operator+(const Complex& right)
            {
                return Complex(re + right.re, im + right.im);
            }

            // Перегрузка оператора вычитания
            Complex operator-(const Complex& right)
            {
                return Complex(re - right.re, im - right.im);
            }

            // Перегрузка оператора умножения
            Complex operator*(const Complex& right)
            {
                return Complex(re * right.re - im * right.im, re * right.im + im * right.re);
            }

            // Перегрузка оператора деления (без проверок знаминателей)
            Complex operator/(const Complex& right)
            {
                double denom = right.re * right.re + right.im * right.im;
                double re_new = ( re * right.re + im * right.im ) / denom;
                double im_new = ( right.re * im - re * right.im ) / denom;
                return Complex(re_new, im_new);
            }
        };

        // После объявления класса можем делать так:
        Complex z1{10.5, 3}, z2{4, 8.8}, z3;
        z3 = z1 + z2;
        z3 = z1 * z2;
        z3 = z2 - z1;
        z3 = z1 / z2;

        // В сущности, каждый оператор представляет собой вызов выше определённых специальных методов класса.
        // Как пример:
        z3 = z1.operator*(z2); // абсолютно аналогично записи z3 = z1 * z2;

    Последняя строчка очень важна для понимания бинарных операторов (операторы, действующие на два аргумента). Она показывает
    на каком объекте будет вызываться оператор как метода класса (в данном случае этот объект - z1), а какой объект
    будет передан в качестве аргумента(z2).

    Что ещё интересно, то это факт, что пример перегрузки операторов демонстрируется любому, кто пользуется библиотекой
    ввода-вывода C++. Сюда входят - cout, cin и операции с файлами через классы-потоки (ifstream, ofstream). Обычно, для
    вывода значения некоторой переменной на экран используется конструкция:
        int num = 10;
        cout << num;
    Здесь знак "<<"  является перегруженным оператором для объекта cout (если точнее, для класса, экземпляром которого
    является cout, но не суть). Сам по себе оператор "<<" - является оператором побитового сдвига влево и предназначен
    для работы с целыми безнаковыми типами. Однако в библиотеке ввода-вывода он был перегружен и выполняет другие
    действия.

    Здесь подходим ко второму способу перегрузки операторо для конкретного класса - через дружественную функцию.
    Допустим, хочется иметь возможность выводить комплексное число следеющим способом:
        cout << z3;

    Фактически, тут происходит следующий вызов метода: cout.operator<<(z3); Но класс объекта cout поменять невозможно - он определён
    в стандартной библиотеке. Таким образом, остаётся только вариант с некоторой функцией:
        // перегрузка оператора вывода определяется один раз,
        // но работает как для cout, так и для любого файлового потока на запись.
        std::ostream& operator<<(std::ostream& os, Complex& z)
        {
            os << std::noshowpos << z.get_re() << std::showpos << z.get_im() << "i";
            return os;
        }

    Синтаксис оператора для вывода стандартен: первым аргументом идёт ссылка на поток вывода (в данном случае - os, не забываем амперсанд),
    вторым - объект нашего класса. В приведённом определении используется тот факт, что класс Complex предоставляет методы для получения
    действительной (get_re) и мнимой частей. Если бы их не было, то пришлось бы определять приведённый выше оператор
    как дружественную функцию для класса:
        class Complex
        {
            double re, im; // комплексное число имеет действительную и мнимую часть, которые являются действительными числами
        public:

            Complex(double _re, double _im) : re{_re}, im{_im}
            {} // простой констуктор

            // пара методов, доступ к текущим значениям целой и действительной части:
            double get_re()
            {
                return re;
            }

            double get_im()
            {
                return im;
            }

            // Перегрузка оператора +. Позволяет делать вот так:
            // Complex z1(1, 2), z2(3.4, 5.5);
            // Complex z3 = z1 + z2;
            Complex operator+(const Complex& right)
            {
                return Complex(re + right.re, im + right.im);
            }

            // Перегрузка оператора вычитания
            Complex operator-(const Complex& right)
            {
                return Complex(re - right.re, im - right.im);
            }

            // Перегрузка оператора умножения
            Complex operator*(const Complex& right)
            {
                return Complex(re * right.re - im * right.im, re * right.im + im * right.re);
            }

            // Перегрузка оператора деления (без проверок знаминателей)
            Complex operator/(const Complex& right)
            {
                double denom = right.re * right.re + right.im * right.im;
                double re_new = ( re * right.re + im * right.im ) / denom;
                double im_new = ( right.re * im - re * right.im ) / denom;
                return Complex(re_new, im_new);
            }

            friend std::ostream& operator<<(std::ostream, Complex&);
        };

        std::ostream& operator<<(std::ostream& os, Complex& z)
        {
            // дружественная функция, как вы помните, имеет доступ к закрытым полям класса напрямую
            os << std::noshowpos << z.re << std::showpos << z.im << "i";
            return os;
        }

    Выбор способа определения оператора - независимая или дружественная функция - определяется тем,
    какие открытые (public) методы этот класс предоставляет и достаточно ли их для вывода.
    После перегруки оператора << можно делать так:
        cout << z3 << endl << z2 << endl;

*/

#include <iostream>
#include <cmath>

using namespace std;

/*
    Продолжение разработки класса FillingMachine.

    Задача для этого класса была сформулирована так: хотим получить класс, описывающий некоторое
    разливочное устройство (резервуар) для жидкости. Основными характеристиками такой штукенции являются:
        * вместимость       - максимальный объём, измеряем в действительных числах
        * текущий уровень   - каков запас жидкости в данный момент. Также измеряется в действительных числах

    А методы класса - будут объяснены ниже. Сам класс будет везде написан по следующему принципу:
        идёт объявление класса (поля + объявления методов), затем функция main, и только после неё
        реализация всех методов класса.

    Изменения:
        -> функция pretty_print заменена на перегрузку оператора <<.
        -> добавлена перегрузка оператора равенства (==) и неравенства (!=)
*/
class FillingMachine
{
    double capacity;            // максимальныя вместимость
    double current_volume;      // текущий объём

public:
    FillingMachine();
    FillingMachine(double init_value);
    FillingMachine(const FillingMachine& other);

    // возращает вместимость конкретного объекта
    double get_capacity();

    // проверяем, есть ли жидкость в объекте. Возращаем булево значение (истина / ложь, они же - true / false).
    bool is_empty();
    // обратная проверка - не заполнен ли объект
    bool is_full();

    // снова заполняем наш резервуар до максимальной вместимости
    void restore_full_volume();


    /*
        Пробуем запросить требуемый объём из резервуара.
        В случае, если запрошенный объём больше текущего количества -
        возращается отрицательное число (как способ обнаружить и обработать ошибку).
    */
    double take_volume(double required_vol);

    /*
        Перегрузка оператора равенства.
        Будем считать объекты равны, если их вместимость и текущий объём совпадают
    */
    bool operator==(const FillingMachine& other);
    bool operator!=(const FillingMachine& other);

    friend ostream& operator<<(std::ostream& os, const FillingMachine& machine);
};

int main()
{
    FillingMachine *fm1, *fm2;

    fm1 = new (nothrow) FillingMachine(10);
    if ( fm1 == nullptr ) {
        cerr << "Error with memory allocation";
        exit(1);
    }

    fm2 = new (nothrow) FillingMachine;
    if ( fm2 == nullptr ) {
        cerr << "Error with memory allocation";
        exit(1);
    }

    cout << "take 4.5 volume from fm1 object. The returned value is " << fm1->take_volume(4.5) << endl;

    cout.setf(ios_base::boolalpha);
    cout << "Is fm1 empty: " << fm1->is_empty() << endl;
    cout << "Is fm1 full: " << fm1->is_full() << endl;

    //cout << ld << endl;

    double result = fm1->take_volume(5.5);
    if (result < 0) {
        cout << "No enough volume at device" << endl;
    }

    cout << "Is fm1 empty: " << fm1->is_empty() << endl;
    cout << "Is fm2 full: "<< fm2->is_full() << endl;

    cout << *fm2 << endl;

    FillingMachine fm3(4.5), fm4(4.5), fm5(5.5);

    if ( fm3 == fm4 ) {
        cout << "fm3 and fm4 are equal!" << endl;
    }

    if ( fm3 != fm5 ) {
        cout << "fm3 and fm5 are not equal!" << endl;
    }

    // освобождаем память под объекты
    delete fm1;
    delete fm2;

    return 0;
}

double FillingMachine::get_capacity()
{
    return capacity;
}

bool FillingMachine::is_empty()
{
    return current_volume <= 0;
}

bool FillingMachine::is_full()
{
    if ( current_volume <= 0 ) {
        return false;
    } else {
        return abs(capacity - current_volume) < 0.0000001;
    }
}

void FillingMachine::restore_full_volume()
{
    current_volume = capacity;
}

double FillingMachine::take_volume(double required_vol)
{
    if ( required_vol > current_volume ) {
        return -1.0;
    }

    current_volume -= required_vol;
    return required_vol;
}

/*
    Констурктор с параметром: устанавливаем одновременно и вместимость, и текущее значение объёма.
*/
FillingMachine::FillingMachine(double initial_cap) :
    capacity{initial_cap}, current_volume{initial_cap}
{
    // Вывод только для понимания работы программы, конечно же в нём смысла нет в реальном классе
    cout << "Constructor FillingMachine(double initial_cap) called" << endl;
}

/*
    Констуруктор копирования
*/
FillingMachine::FillingMachine(const FillingMachine& other) : capacity{other.capacity}, current_volume{other.current_volume}
{
    // Вывод только для понимания работы программы, конечно же в нём смысла нет в реальном классе
    cout << "Copy constructor called" << endl;
}

/*
    Конструктор по умолчанию.
    Пусть присваивает значение 25.0 для capacity и current_volume
*/
FillingMachine::FillingMachine() : capacity{25.0}, current_volume{25.0}
{
    cout << "Default constructor called" << endl;
}

ostream& operator<<(std::ostream& os, const FillingMachine& machine)
{
    os << "[[Filling machine with capacity: " << machine.capacity << ", and current volume: " << machine.current_volume << "]]";
    return os;
}

// Перегрузка операторов равенства
bool FillingMachine::operator==(const FillingMachine& other)
{
    return capacity == other.capacity && current_volume == other.current_volume;
}

bool FillingMachine::operator!=(const FillingMachine& other)
{
    return capacity != other.capacity && current_volume != other.current_volume;
}
