/**
    Задумка для собственного типа данных: релализовать динамический массив
    с возможностью положительных и отрицательных индексов.

    Пример массива:  [ 10.5, 5.6, -9.3, 11.1, 0.567 ]
       '+' индексы:     0     1     2     3     4
       '-' индексы:    -5    -4    -3    -2    -1

    Условия на создаваемый тип:
        - создание массива заданной размерности;
        - создание массива заданной размерности и заполнение каждого элемента
          конкретным значением;
        - нет проверки выхода индекса массива за его границы;

    ==================================================================

    Переходим от массива, хранящего элементы строго определённого типа (double в предудыщем
    примере) к шаблонному классу динамического массива с циклическими индексами, который
    может хранить значения произвольного типа.
*/

#include <algorithm>
/**
    следующий заголовочный файл нужен для того, чтобы
    была возможность создавать массив следующим образом:
        // динамический массив строк из четырёх конкретных элементов
        DynArray<string> array_of_strings = {"На", "первый", "второй", "рассчитайсь"};
*/
#include <initializer_list>

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

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
    Данный класс подходит для создания динамических массивов любых типов,
    которые поддерживают копирование.
*/
template<typename TValue>
class DynArray
{
public:
    /// Данные псевдонимы не обязательно, но так определяются типы
    /// в стандартной библиотеке C++. И некоторые функции из <algorithm>
    /// могут полагяться на них. Поэтому, сделаем по уму
    using value_type = TValue;
    using iterator = TValue*;
    using const_iterator = const TValue *;

    /**
        Конструктор без параметров, создаёт "нулевой" массив
    */
    DynArray() = default;
    /**
        Конструктор с одним параметром:
            создаёт динамический массив на число элементов,
            заданных значением параметра *array_size*.
    */
    DynArray(size_t array_size);
    /**
        Конструктор с двумя параметрами:
            создаёт динамический массив на число элементов,
            заданных значением параметра *array_size* и
            каждому элементу присваивает значение *value*.
    */
    DynArray(size_t array_size, const TValue& value);

    /**
        Конструктор копий:
            создаёт копию другого динамического массива типа DynArray1D.

        Нужен для предотвращения копирования по умолчанию, когда в разные
        переменные-объекты данного типа попадают адреса одного и того же
        блока динамической памяти.
    */
    DynArray(const DynArray& other);

    /**
        Перемещающий конструктор (move-constructor).

        Специальный тип конструктора, который используется в некоторых ситуациях,
        когда динамическое (как правило) содержимое объекта можно передать другому,
        вновь создаваемому. А в первоначальном объекте об этом содержимом просто забыть.
    */
    DynArray(DynArray&& other);

    /**
        Деструктор:
            автоматически удаляет динамическую память, когда перемнная
            данного класса выходит из области видимости.
    */
    ~DynArray();

    /// Методы класса
    /// Узнать длину конкретного объекта данного типа
    size_t length() const;
    /// Узнать ёмкость конкретного объекта данного типа
    size_t capacity() const;

    /// Изменить размер массива:
    void resize(size_t new_size);
    /// Привести размер используемой динамической памяти к реальной длине массива
    void fit();

    /// Добавить элемент *elem* в конец массива
    DynArray& add_last(const value_type& elem);
    /// Добавить элемент *elem* на место массива, которое указывается индексом *index*
    DynArray& add(int index, const value_type& elem);

    /// Удалить последний элемент:
    DynArray& remove_last();
    /// Удалить элемент по индексу:
    DynArray& remove_at(int index);
    /**
        Удалить диапазон элементов [first; last] по паре индексов.
        Индексы могут быть как положительные, так и отрицательные.
        Примеры:
            my_arr.remove_at(0, 3) - удаление первых четырёх элементов
            my_arr.remove_at(0, -2) - удалить все элементы с первого до последнего
            my_arr.remove_at(-3, -1) - удалить элементы с индексами -3, -2, -1.
    */
    DynArray& remove_at(int first, int last);

    /// Перегруженные операторы
    /**
        Оператор "квадратные скобки" используется для обращения к элементам
        массива по положительному или отрицательному индексу.

        Возращает ссылку на конкретный элемент.
    */
    TValue& operator[](int index);
    /// Эта версия нужна, чтобы обращаться к элементам константных объектов класса
    const TValue& operator[](int index) const;

    /// Оператор "<<" перегружен для добавления элементов в конкретный массив.
    DynArray& operator<<(const value_type& value);

    /// Оператор присваивания - перегружен для правильно копирования одного объекта массива в другой.
    void operator=(const DynArray& other);

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
        и с их неизменяемыми значениями.
    */
    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

private:
    /**
        Поля класса DynArray.
            - _arr - указатель, использующийся для хранения элементов массива;
            - _length - текущая длина массива;
            - _capacity - текущая ёмкость массива, т.е. количество элементов
            типа TValue, которые уже выделены в виде динамической памяти.

        Для каждого из полей указаны значения по умолчанию.
    */
    TValue *_arr = nullptr;
    size_t _length = 0;
    size_t _capacity = 0;
};


/**
    В дополнении к методам, реализуем и свободные функции для получения итераторов.

    Они становятся шаблонными функциями.

    Для того, чтобы указать возвращаемое значение или переменную, зависящую от
    шаблонного класса, нужно указать ключевое слово *typename* перед названием
    типа
*/
template<typename TValue>
typename DynArray<TValue>::iterator begin(DynArray<TValue>& obj)
{
    return obj.begin();
}

template<typename TValue>
typename DynArray<TValue>::iterator end(DynArray<TValue>& obj)
{
    return obj.end();
}

/**
    Демонстрация перегрузки оператора вывода для *улучшенного* вывода массива
    в текстовый вид.

    Перегрузка операторов ввода-вывода должна осуществляться только в виде функций,
    не методов класса.

    Польза от итераторов должна быть видна.

    Функция для перегрузки оператора <<вывода>> тоже может быть шаблонной.
*/
template<typename TValue>
std::ostream& operator<<(std::ostream& os, const DynArray<TValue>& obj)
{
    os << "[";
    typename DynArray<TValue>::const_iterator last = obj.end() - 1;
    for (typename DynArray<TValue>::const_iterator it = obj.begin(); it != obj.end(); it++ ) {
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
    DynArray<double> vec{10, 444.5};

    cout << vec.length() << endl;
    vec[-4] = 15.0;

    vec.add_last(3.7).add_last(6.8).add_last(-7.7);
    vec << 9.88 << 33.33323;

    cout << "Массив vec: "<< vec << endl;

    DynArray<double> another_array{2};
    another_array = vec;
    /// Сортировка работает для объектов класса DynArray<double>
    sort(begin(another_array), end(another_array));
    cout << another_array << endl;

    another_array.remove_last().remove_last().remove_at(-9);
    cout << "После удаления:\n" << another_array << endl;

    cout << "Ёмкость vec:\n\t" << vec.capacity() << endl;
    vec.fit();
    cout << "Ёмкость vec после подгонки под актуальный размер:\n\t" << vec.capacity() << endl;

    vec.remove_at(-5, -2);
    cout << "Длина vec после удаления по диапазону:\n\t" << vec.length() << endl << vec << endl;

    vec.resize(5);
    cout << "Длина vec после изменения размера: " << vec.length() << endl << vec << endl;

    vec.add(1, 555.999).add(-1, 3.14);
    cout << "Итоговый vec: " << vec << endl;

    /// Демонстрация работы перемещающего конструктора.
    /// После вызова std::move в переменной vec не останется ссылки на динамический массив.
    DynArray<double> new_vec = std::move(vec);
    cout << "Старый вектор под новой переменной: " << new_vec << endl;
    cout << "Размер vec: " << vec.length() << endl;
}

/**
    Далее следуют определения конструкторов и методов шаблонного класса.
    Кажому из них теперь положено добавление конструкции
        template<typename TValue>
*/
/// Определение конструкторов и деструктора:
template<typename TValue>
DynArray<TValue>::DynArray(size_t array_size)
{
    _arr = new TValue[array_size];
    _length = _capacity = array_size;
}

template<typename TValue>
DynArray<TValue>::DynArray(size_t array_size, const TValue& value)
{
    _arr = new TValue[array_size];
    _length = _capacity = array_size;

    for (size_t i = 0; i < _length; i++) {
        _arr[i] = value;
    }
}

template<typename TValue>
DynArray<TValue>::DynArray(const DynArray<TValue>& other)
{
    _length = other._length;
    _capacity = other._capacity;
    _arr = new TValue[_capacity];

    for (size_t i = 0; i < _length; i++) {
        _arr[i] = other._arr[i];
    }
}

/// Перемещающий конструктор
template<typename TValue>
DynArray<TValue>::DynArray(DynArray&& other)
{
    _length = other._length;
    _capacity = other._capacity;
    /**
        Передаём динамический массив от объекта *other*
        текущему создаваемому объекту. Никакого нового
        выделения динамической памяти не происходит.
    */
    _arr = other._arr;

    /**
        У объекта *other* стираем ссылку на динамический массив,
        для завершения перемещания ресурса.
    */
    other._arr = nullptr;
    other._length = other._capacity = 0;
}

template<typename TValue>
DynArray<TValue>::~DynArray()
{
    delete[] _arr;
}

/// Определение методов-класса:
template<typename TValue>
size_t DynArray<TValue>::length() const
{
    return _length;
}

template<typename TValue>
size_t DynArray<TValue>::capacity() const
{
    return _capacity;
}

template<typename TValue>
TValue& DynArray<TValue>::operator[](int index)
{
    if (index >= 0) {
        return _arr[index];
    }

    return _arr[_length + index];
}

template<typename TValue>
const TValue& DynArray<TValue>::operator[](int index) const
{
    if (index >= 0) {
        return _arr[index];
    }

    return _arr[_length + index];
}

template<typename TValue>
DynArray<TValue>& DynArray<TValue>::operator<<(const TValue& value)
{
    return add_last(value);
}

template<typename TValue>
void DynArray<TValue>::operator=(const DynArray<TValue>& other)
{
    delete[] _arr;

    _length = other._length;
    _capacity = other._capacity;
    _arr = new TValue[_capacity];

    for (size_t i = 0; i < _length; i++) {
        _arr[i] = other._arr[i];
    }
}

/// Возвращаем указатель на первый элемент массива
template<typename TValue>
typename DynArray<TValue>::iterator DynArray<TValue>::begin()
{
    return _arr;
}

template<typename TValue>
typename DynArray<TValue>::const_iterator DynArray<TValue>::begin() const
{
    return _arr;
}

/// Возвращаем указатель на элемент, которые следует за последним
/// элементом массива
template<typename TValue>
typename DynArray<TValue>::iterator DynArray<TValue>::end()
{
    return _arr + _length;
}

template<typename TValue>
typename DynArray<TValue>::const_iterator DynArray<TValue>::end() const
{
    return _arr + _length;
}

/// Удалить последний элемент: просто делаем длину массива на
/// единицу меньше. Реального удаления не происходит.
template<typename TValue>
DynArray<TValue>& DynArray<TValue>::remove_last()
{
    _length--;
    return *this;
}

/// Удалить элемент по индексу: тут похитрее, надо
/// все элементы за удаляемым сдвинуть на позицию вправо.
/// Опять же, реально не отчищаем динамиескую память
template<typename TValue>
DynArray<TValue>& DynArray<TValue>::remove_at(int index)
{
    int pos_index = (index >= 0) ? index : _length + index;

    for (size_t i = size_t(pos_index) + 1; i < _length; i++) {
        _arr[i-1] = _arr[i];
    }

    _length--;
    return *this;
}

/**
    Удалить диапазон элементов [first; last] по паре индексов.
    Индексы могут быть как положительные, так и отрицательные.
    Примеры:
        my_arr.remove_at(0, 3) - удаление первых четырёх элементов
        my_arr.remove_at(0, -2) - удалить все элементы с первого до предпоследнего
        my_arr.remove_at(-3, -1) - удалить элементы с индексами -3, -2, -1.
*/
template<typename TValue>
DynArray<TValue>& DynArray<TValue>::remove_at(int first, int last)
{
    const int first_ind = (first >= 0) ? first : _length + first;
    const int last_ind = (last >= 0) ? last : _length + last;
    std::cout << "[remove_at, range]: [" << first_ind << ", " << last_ind << "]" << endl;

    if (first_ind > last_ind) {
        /// Неправильный диапазон индексов, ничего не делаем
        return *this;
    }

    /// Берём все элементы, после удаляемого и сдвигаем их вправо.
    /// При удалении не требуется перераспределения памяти.
    size_t cur_ind = size_t(first_ind);
    for (size_t i = size_t(last_ind) + 1; i < _length; i++) {
        _arr[cur_ind] = _arr[i];
        cur_ind++;
    }
    /// Устанавливаем новую длину массива.
    _length -= (last_ind - first_ind) + 1;

    return *this;
}

/// Изменить размер массива:
template<typename TValue>
void DynArray<TValue>::resize(size_t new_size)
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

    TValue* new_da = new TValue[_capacity];
    for (size_t i = 0; i < _length; i++) {
        new_da[i] = _arr[i];
    }
    delete[] _arr;
    _arr = new_da;
}

/// Привести размер используемой динамической памяти к реальной длине массива
template<typename TValue>
void DynArray<TValue>::fit()
{
    if (_length != _capacity) {
        _capacity = _length;

        TValue* new_da = new TValue[_capacity];
        for (size_t i = 0; i < _length; i++) {
            new_da[i] = _arr[i];
        }
        delete[] _arr;
        _arr = new_da;
    }
}

/// Добавить элемент *elem* в конец массива
template<typename TValue>
DynArray<TValue>& DynArray<TValue>::add_last(const value_type& elem)
{
    if (_capacity == 0) {
        _capacity = 8;
        _arr = new TValue[_capacity];

        _arr[0] = elem;
        _length++;
        return *this;
    }

    if (_capacity == _length) {
        _capacity *= 2;
        TValue* ptr = new TValue[_capacity];

        for (size_t i = 0; i < _length; i++) {
            ptr[i] = _arr[i];
        }

        ptr[_length] = elem;
        _length++;

        delete[] _arr;
        _arr = ptr;
        return *this;
    }

    _arr[_length] = elem;
    _length++;

    return *this;
}

/// Добавить элемент *elem* на место массива, которое указывается индексом *index*
template<typename TValue>
DynArray<TValue>& DynArray<TValue>::add(int index, const value_type& elem)
{
    size_t pos_index = size_t( (index >= 0) ? index : _length + index );

    if (_length + 1 <= _capacity) {
        /// ёмкости хватает для добавления ещё одного элемента
        for (size_t i = _length; i > pos_index; i--) {
            _arr[i] = _arr[i - 1];
        }
        _arr[pos_index] = elem;
        _length++;
    } else {
        /// заморочки с выделением памяти
        _capacity *= 2;
        TValue* ptr = new TValue[_capacity];

        for (size_t i = 0; i < pos_index; i++) {
            ptr[i] = _arr[i];
        }

        ptr[pos_index] = elem;

        for (size_t i = pos_index + 1; i <= _length; i++) {
            ptr[i] = _arr[i-1];
        }
        _length++;
        delete[] _arr;
        _arr = ptr;
    }

    return *this;
}
