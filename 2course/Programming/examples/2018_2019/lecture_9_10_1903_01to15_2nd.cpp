/**
    В дополнении к версии "1nd" добавлено:
        - очень простой прототип итератора для класса динамического массива.
        Позволяет продемонстрировать идею: как собственные типы-контейнеры
        подружить со стандартной библиотекой C++

        - перегрузка оператора вывода в произвольный поток для класса DynArray1D.
        Эта возможность позволяет отобразить любой собственный объект в текстовом виде
        для вывода на экран, или записи в файл.

        - знакомство с шаблонами: первые шаблонные функции, первая шаблонная структура.
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

double rand_a_b(double a, double b)
{
    static mt19937_64 gnr{ time(nullptr) };
    static const size_t max_gnr = gnr.max();

    return a + (b - a) * ( double(gnr()) / max_gnr );
}


/**
    Задумка для собственного типа данных: релализовать динамический массив
    действительных чисел с возможностью положительных и отрицательных индексов.

    Пример массива:  [ 10.5, 5.6, -9.3, 11.1, 0.567 ]
       '+' индексы:     0     1     2     3     4
       '-' индексы:    -5    -4    -3    -2    -1

    Условия на создаваемый тип:
        - создание массива заданной размерности;
        - создание массива заданной размерности и заполнение каждого элемента
          конкретным значением;
        - нет проверки выхода индекса массива за его границы;

*/
class DynArray1D
{
public:
    /**
        Конструктор с одним параметром:
            создаёт динамический массив на число элементов,
            заданных значением параметра *array_size*.
    */
    DynArray1D(size_t array_size);
    /**
        Конструктор с двумя параметрами:
            создаёт динамический массив на число элементов,
            заданных значением параметра *array_size* и
            каждому элементу присваивает значение *value*.
    */
    DynArray1D(size_t array_size, double value);

    /**
        Конструктор копий:
            создаёт копию другого динамического массива типа DynArray1D.

        Нужен для предотвращения копирования по умолчанию, когда в разные
        переменные-объекты данного типа попадают адреса одного и того же
        блока динамической памяти.
    */
    DynArray1D(const DynArray1D& other);

    /**
        Деструктор:
            автоматически удаляет динамическую память, когда перемнная
            данного класса выходит из области видимости.
    */
    ~DynArray1D();
    /// Методы класса
    /// Узнать длину конкретного объекта данного типа
    size_t length() const;
    /// Узнать ёмкость конкретного объекта данного типа
    size_t capacity() const;

    /// Перегруженные операторы
    /**
        Оператор "квадратные скобки" используется для обращения к элементам
        массива по положительному или отрицательному индексу.

        Возращает ссылку на конкретный элемент.
    */
    double& operator[](int index);
    /**
        Оператор "<<" перегружен для добавления элементов в конкретный массив.
    */
    DynArray1D& operator<<(double value);
    /// Оператор присваивания - перегружен для правильно копирования одного объекта массива в другой.
    void operator=(const DynArray1D& other);

private:
    /**
        Поля класса DynArray1D.
            - _arr - указатель, использующийся для хранения элементов массива;
            - _length - текущая длина массива;
            - _capacity - текущая ёмкость массива, т.е. количество элементов
            типа double, которые уже выделены в виде динамической памяти.

        Для каждого из полей указаны значения по умолчанию.
    */
    double *_arr = nullptr;
    size_t _length = 0;
    size_t _capacity = 0;
};

/**
    Очень наивная реализация итератора для класса DynArray1D.

    Концепция итератора для типов-контейнеров (типы, предназначенные для
    хранения набора некоторрых элементов) заключается в следующем:
    итератор это специальный объект, который переберает содержимое контейнера
    и позволяет получать доступ к его элементам. Далее условно обозначать
    итератор символами it. Итератор для работы со стандартной библиотекой
    C++ должен поддерживать, как минимум, следующие операции:
        * "it++" - инкремент, переход к следующему элементу;
        * "*it" - разыменование, получение значения элемента;
        * "==, !=" - проверка на равенство и не равенство.

    Требования выше очень похожи на работу с указателями в C++. В этом заключается
    одна из идей использования концепции итераторов в C++: как был не была сложна
    структура контейнера, работа с перебором элементов сводится к инкрементированию
    указатель-подобного объекта.

    Для предоставления итераторов для конкретного типа данных, в C++ существует
    2 подхода:
        1. Объявление свободных функций *begin* и *end*, которые будут возращать
        итераторы на первый и последний элементы, соответственно.

        2. Определение *begin* и *end* как методов класса.
    По согласованию с коллективом ФПБ-703-О1-01 выбран первый вариант.

    Вместо определения нового типа, представляющего итератор для DynArray1D,
    выбран упрощённый способ - воспольноваться возращением внутренних указателей
    конкретныъ объектов DynArray1D.

    *begin* - возращает адрес первого элемента;
    *end* - элемента, следующего за последним.

    Имя параметра эксклюзивно и на безвозмездной основе придумано и передано
    данному примеру Сухачёвым Русланом Артуровичем 15.03.2019.
*/
double* begin(DynArray1D& igor)
{
    return &igor[0];
}

double* end(DynArray1D& igor)
{
    return &igor[ igor.length() ];
}

/**
    Демонстрация перегрузки оператора вывода для *улучшенного* вывода массива
    в текстовый вид.

        *улучшенного* - насколько захотел придумать коллектив группы ФПБ-703-О1-01 15.03.2019
*/
std::ostream& operator<<(std::ostream& os, DynArray1D& da)
{
    for (const double& elem : da) {
        os << '"' << elem << "\", ";
    }

    return os;
}

/**
    Далее идёт демонстрация шаблонных функций и шаблонной структуры.
*/
template <typename Type>
void print_arr(Type arr[], size_t sz)
{
   for (size_t i = 0; i < sz; i++) {
        cout << arr[i] << ' ';
   }
   cout << endl;
}

template <typename Type>
void fill_static_array(Type arr[], size_t sz)
{
    for (size_t i = 0; i < sz; i++) {
        cout << "Enter " << i + 1
             << " element: ";
        cin >> arr[i];
    }
}

template <typename Type>
void my_swap(Type& first, Type& second)
{
    Type tmp = first;
    first = second;
    second = tmp;
}

template <typename T1, typename T2>
struct Pair
{
   T1 first;
   T2 second;
};

int main()
{
    /// Часть 1
    DynArray1D vec{10, 444.5};

    cout << vec.length() << endl;
    vec[-4] = 15.0;

    vec << 3.7 << 6.8 << 9.88 << 33.33323;

    cout << "Массив vec: "<< vec << endl;

    DynArray1D another_array{2};
    another_array = vec;

    /// Сортировка работает для объектов класса DynArray1D
    sort(begin(another_array), end(another_array));

    cout << another_array << endl;

    /// Часть 2
    string mas[4];
    fill_static_array(mas, 4);
    print_arr(mas, 4);

    int i_mas[4];
    fill_static_array(i_mas, 4);
    print_arr(i_mas, 4);

    Pair<double, string> p1 = {5.434884, "a string"};
    cout << p1.first << endl;
}

/// Определение конструкторов и деструктора:
DynArray1D::DynArray1D(size_t array_size)
{
    _arr = new double[array_size];
    _length = _capacity = array_size;
}

DynArray1D::DynArray1D(size_t array_size, double value)
{
    _arr = new double[array_size];
    _length = _capacity = array_size;

    for (size_t i = 0; i < _length; i++) {
        _arr[i] = value;
    }
}

DynArray1D::DynArray1D(const DynArray1D& other)
{
    _length = other._length;
    _capacity = other._capacity;
    _arr = new double[_capacity];

    for (size_t i = 0; i < _length; i++) {
        _arr[i] = other._arr[i];
    }
}

DynArray1D::~DynArray1D()
{
    delete[] _arr;
}

/// Определение методов-класса:
size_t DynArray1D::length() const
{
    return _length;
}

size_t DynArray1D::capacity() const
{
    return _capacity;
}

double& DynArray1D::operator[](int index)
{
    if (index >= 0) {
        return _arr[index];
    }

    return _arr[_length + index];
}

DynArray1D& DynArray1D::operator<<(double value)
{
    if (_capacity == 0) {
        _capacity = 8;
        _arr = new double[_capacity];

        _arr[0] = value;
        _length++;
        return *this;
    }

    if (_capacity == _length) {
        double *ptr = new double[2 * _capacity];
        _capacity *= 2;

        for (size_t i = 0; i < _length; i++) {
            ptr[i] = _arr[i];
        }

        ptr[_length] = value;
        _length++;

        delete[] _arr;
        _arr = ptr;
        return *this;
    }

    _arr[_length] = value;
    _length++;

    return *this;
}

void DynArray1D::operator=(const DynArray1D& other)
{
    cout << "Operator= called" << endl;
    delete[] _arr;

    _length = other._length;
    _capacity = other._capacity;
    _arr = new double[_capacity];

    for (size_t i = 0; i < _length; i++)
    {
        _arr[i] = other._arr[i];
    }
}

