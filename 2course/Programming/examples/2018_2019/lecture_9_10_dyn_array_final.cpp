/**
    Отдельный файл для реализации динамического массива для
    элементов типа double
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
        Конструктор без параметров, создаёт "нулевой" массив
    */
    DynArray1D() = default;
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
    /// Удалить последний элемент:
    DynArray1D& remove_last();
    /// Удалить элемент по индексу:
    DynArray1D& remove_at(int index);
    /// Изменить размер массива:
    void resize(size_t new_size);
    /// Привести размер используемой динамической памяти к реальной длине массива
    void fit();

    /// Перегруженные операторы
    /**
        Оператор "квадратные скобки" используется для обращения к элементам
        массива по положительному или отрицательному индексу.

        Возращает ссылку на конкретный элемент.
    */
    double& operator[](int index);
    /// Эта версия нужна, чтобы обращаться к элементам константных объектов класса
    const double& operator[](int index) const;
    /**
        Оператор "<<" перегружен для добавления элементов в конкретный массив.
    */
    DynArray1D& operator<<(double value);
    /// Оператор присваивания - перегружен для правильно копирования одного объекта массива в другой.
    void operator=(const DynArray1D& other);

    /// Методы для предоставления итераторов
    /**
        Наивная реализация итератора для класса DynArray1D.

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

        Дублирование методов нужно, чтобы язык мог работать и с объектами класса,
        и с их константами.
    */
    double* begin();
    const double * begin() const;

    double* end();
    const double * end() const;

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
    В дополнении к методам, реализуем и свободные функции для получения итераторов
*/
double* begin(DynArray1D& obj)
{
    return obj.begin();
}

double* end(DynArray1D& obj)
{
    return obj.end();
}

/**
    Демонстрация перегрузки оператора вывода для *улучшенного* вывода массива
    в текстовый вид.

    Перегрузка операторов ввода-вывода должна осуществляться только в виде функций,
    не методов класса.

    Польза от итераторов должна быть видна.
*/
std::ostream& operator<<(std::ostream& os, const DynArray1D& obj)
{
    os << "[";
    const double *last = obj.end() - 1;
    for (const double* it = obj.begin(); it != obj.end(); it++ ) {
        os << *it;
        if (it != last) {
            os << ", ";
        }

    }
    os << "]";

    return os;
}

int main()
{
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

    another_array.remove_last().remove_last().remove_at(-9);
    cout << "После удаления:\n" << another_array << endl;

    cout << "Ёмкость vec:\n\t" << vec.capacity() << endl;
    vec.fit();
    cout << "Ёмкость vec после подгонки под актуальный размер:\n\t" << vec.capacity() << endl;

    vec.resize(5);
    cout << "Длина vec после изменения размера: " << vec.length() << endl << vec;
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

const double& DynArray1D::operator[](int index) const
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

    /**
        БОНУСНАЯ ЗАДАЧА для прикладников:
            * можно ли оптимизировать копирование элементов из одного
            массива в другой?

        HINT: найти в документации функцию memcpy, разобраться как работает,
        поменять перебор всех элементов на её вызов.
    */
    for (size_t i = 0; i < _length; i++) {
        _arr[i] = other._arr[i];
    }
}

/// Возвращаем указатель на первый элемент массива
double* DynArray1D::begin()
{
    return _arr
}

const double * DynArray1D::begin() const
{
    return _arr
}

/// Возвращаем указатель на элемент, которые следует за последним
/// элементом массива
double* DynArray1D::end()
{
    return _arr + _length;
}

const double * DynArray1D::end() const
{
    return _arr + _length;
}

/// Удалить последний элемент: просто делаем длину массива на
/// единицу меньше. Реального удаления не происходит.
DynArray1D& DynArray1D::remove_last()
{
    _length--;
    return *this;
}

/// Удалить элемент по индексу: тут похитрее, надо
/// все элементы за удаляемым сдвинуть на позицию вправо.
/// Опять же, реально не отчищаем динамиескую память
DynArray1D& DynArray1D::remove_at(int index)
{
    int pos_index = (index >= 0) ? index : _length + index;

    for (size_t i = size_t(pos_index) + 1; i < _length; i++) {
        _arr[i-1] = _arr[i];
    }

    _length--;
    return *this;
}
/// Изменить размер массива:
void DynArray1D::resize(size_t new_size)
{
    if (new_size == _capacity) {
        return;
    }

    if (new_size < _capacity) {
        _capacity = new_size;

        if (_length > _capacity) {
            _length = _capacity;
        }
    }

    double *new_da = new double[_capacity];
    for (size_t i = 0; i < _length; i++) {
        new_da[i] = _arr[i];
    }
    delete[] _arr;
    _arr = new_da;
}

/// Привести размер используемой динамической памяти к реальной длине массива
void DynArray1D::fit()
{
    if (_length != _capacity) {
        _capacity = _length;

        double *new_da = new double[_capacity];
        for (size_t i = 0; i < _length; i++) {
            new_da[i] = _arr[i];
        }
        delete[] _arr;
        _arr = new_da;
    }
}
