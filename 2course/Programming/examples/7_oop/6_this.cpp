/*
    !Все файлы с номерами меньше текущего в одной директории - обязательны к прочтению в порядке возрастания номеров!

    Наконец короткая заметка.

    В каждом методе класса неявно доступен указатель на его внутреннуюб структуру. Такой указатель
    обозначается ключевым словом this.

        class TestCl
        {
            int n1, n2;
        public:
            TeslCl() : n1(1), n2(4)
            {}

            void set_n1(int _n1)
            {
                // пример использования this
                // Этот указатель содержит в себе все поля класса.
                this->n1 = _n1; // полный эквивалент n1 = _n1, но записанный в явном виде.
            }

            // Указатель this даёт возможность делать некоторые интересные вещи с объектами классов
            // Пусть определены следующие два метода:
            TestCl& print_n1()
            {
                cout << "n1 = " << n1 << endl;
                // поскольку возращаемое значение - сам объект, то требуется разыменование указателя
                return *this
            }

            TestCl& print_n2()
            {
                cout << "n1 = " << n1 << endl;
                return *this
            }

        };

        TeslCl t1;
        t1.set_n1(10);
        t1.set_n2(3);

        // За счёт возращаемого значения типа TestCl и использования указателя this, можно организовывать вот
        // такие цепочки вызовов для одного объекта.
        t1.print_n1().print_n2().set_n2(5);
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
        -> в методе restore_full_volume используется указатель this (только для демо, необходимости в данном случае в нём нет!)
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
    this->current_volume = this->capacity;
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
