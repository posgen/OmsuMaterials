/*
    !Все файлы с номерами меньше текущего в одной директории - обязательны к прочтению в порядке возрастания номеров!

    Для начала, вспоминаем отличия метода класса от обычной функции. С точки зрения использования,
    есть два ключевых отличия:
        -> методы класса имеют прямой доступ ко всей закрытой (private) части;
        -> методы класса вызываются только для конркетных переменных (объектов класса).
    Опять рассматриваем простой класс из предыдущих файлов:

        class TestCl
        {
            int num;
            char symb;

        public:
            TestCl(int _num, char _symb) : num{_num}, symb{_symb}
            {}

            TestCl() : num{9}, symb{'+'}
            {}

            void change_num(int another)
            {
                // тут обращаемся к закрытой переменной num
                num += another;
            }

            int get_num()
            {
                return num;
            }
        };

        TestCl t1, t2(8, 'v');
        cout << t2.get_num() << endl;

    Выше более-менее всё очевидно: есть два метода класса - change_num и get_num - они выполняют
    некоторые действия с полем num. Но ещё интереснее становится, если в метод класса передать
    переменную того же типа данных. Добавим к классу выше ещё один метод:

        class TestCl
        {
            int num;
            char symb;

        public:
            TestCl(int _num, char _symb) : num{_num}, symb{_symb}
            {}

            TestCl() : num{9}, symb{'+'}
            {}

            void change_num(int another)
            {
                // тут обращаемся к закрытой переменной num
                num += another;
            }

            // пользуясь перегрузкой функций, добавляем версию метода change_num,
            // которая принимает в качестве аргумента - другой объект нашего же класса
            void change_num(TestCl another_obj)
            {
                // Вот самая интересная строчка:
                // можно получить доступ к скрытым полям класса не только для объекта,
                // для которого будет вызван метод change_num, но и для любого другого
                // объекта того же самого класса (another_num в данном случае)
                num += another_obj.num;
            }

            int get_num()
            {
                return num;
            }
        };

        TestCl t1, t2(8, 'v');
        cout << t2.get_num() << endl;
        t1.change_num(t2); // вызов версии change_num, которая принимает переменную того же класса

    Строка 67 демонстрирует ещё одну особенность методов класса: они имеют доступ к закрытым полям
    любого объекта того же класса, переданного в качестве аргумента. Обыкновенная функция, объявленная
    вне класса так не может:

        void do_something(TestCl t)
        {
            // Ниже - ошибка компиляции - обращение к закрутому полю класса
            cout << t.num << endl;
        }

        do_something(t1);

    В дополнении к имеющимся возможностям, в C++ был добавлен механизм *дружественных* функций (friend functions).
    Их главной особенностью является возможность получения доступа к закрытой части переданного в такую функцию
    объекта определённого класса. Дружественные функции описываются в классе и отличаются наличием ключевого слова
    - friend - перед типом возращаемого значения.

        class TestCl
        {
            int num;
            char symb;

        public:
            TestCl(int _num, char _symb) : num{_num}, symb{_symb}
            {}

            TestCl() : num{9}, symb{'+'}
            {}

            void change_num(int another)
            {
                // тут обращаемся к закрытой переменной num
                num += another;
            }

            void change_num(TestCl another_obj)
            {
                num += another_obj.num;
            }

            int get_num()
            {
                return num;
            }

            // объявление дружественных фукнций
            // на аргументы функций не накладывается никаких ограничений
            friend void print_object(TestCl t);
            friend int get_sum_of(TestCl t, int another_num);
        };

        // определение первой дружественной функции
        // здесь ключевое слово слово friend не используется, иначе - ошибка компиляции
        void print_object(TestCl t)
        {
            // обращаемся к закрытым полям объекта t, и никакой ошибки не будет
            cout << "[[TestCl object: {" << t.num << ";;;" << t.symb << "}]]" << endl;
        }

        // и второй
        int get_sum_of(TestCl t, int another_num)
        {
            return t.num + another_num;
        }

    За сим вся магия дружественных функций заканчивается.
*/

#include <iostream>
#include <cmath>

using namespace std;

/*
    Данный файл - только начала набора программ по ООП, в котором на примере
    последовательной модернизации одного и того же класса будут показаны основные особенности
    объектного программирования в C++.

    Задачу для этого класса сформулируем так: хотим получить класс, описывающий некоторое
    разливочное устройство (резервуар) для жидкости. Основными характеристиками такой штукенции являются:
        * вместимость       - максимальный объём, измеряем в действительных числах
        * текущий уровень   - каков запас жидкости в данный момент. Также измеряется в действительных числах

    А методы класса - будут объяснены ниже. Сам класс будет везде написан по следующему принципу:
        идёт объявления класса (поля + объявления методов), затем функция main, и только после неё
        реализация всех методов класса.

    Изменения:
        -> добавлена дружественная функция pretty_print для демонстрации механизма friend functions.
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

    friend void pretty_print(const FillingMachine& machine);
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

    pretty_print(*fm2);

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

void pretty_print(const FillingMachine& machine)
{
    cout << "[[Filling machine with capacity: " << machine.capacity << ", and current volume: " << machine.current_volume << "]]" << endl;
}
