/***
    Пример преобразования класса динамического массива из первого семестра
    в шаблонный класс, подходящий для создания динамических массивов для
    (практически) любых типов данных.
*/
#ifndef FPTARRAY_INCLUDED
#define FPTARRAY_INCLUDED

#include <cstddef>
#include <initializer_list>
#include <algorithm>

template <typename TElem>
class FPTArray
{
public:
    FPTArray() = default;
    FPTArray(size_t arr_sz);
    FPTArray(const FPTArray& other);

    /// FPTArray arr = {2, 3, 4, 5, 6, 7, 8};
    FPTArray(const std::initializer_list<TElem>& lst) :
        data_{new TElem[lst.size()]}, length_{lst.size()}, capacity_{lst.size()}
    {
        size_t i = 0;
        for (const TElem& elem : lst) {
            data_[i] = elem;
            i++;
        }
    }

    FPTArray(FPTArray&& other);
    ~FPTArray();

    FPTArray& operator=(const FPTArray& rhs);
    FPTArray& operator=(FPTArray&& rhs);

    TElem& operator[](size_t index);
    // Специальная перегрузка для возможности использования констант
    // данного типа (как напрямую, так и в качестве параметров функций)
    const TElem& operator[](size_t index) const;

    /**
        Какой-то набор методов для работы с объектами класса.
    */
    TElem back() const;
    TElem front() const;
    size_t length() const;
    TElem pop();
    void push(const TElem& new_elem);

    /**
        Специальные методы, возвращающие итераторы (объекты) на первый элемент (begin)
        и специальное значение (end), которое сигнализирует о том, что проход по коллекции
        завершился.
    */
    TElem* begin();
    TElem* end();

    /// Для работы с константными объектами этого класса
    const TElem* begin() const;
    const TElem* end() const;

private:
    /**
        Поля для реализации динамического массива.
    */
    TElem *data_ = nullptr;
    size_t length_ = 0;
    size_t capacity_ = 0;

    void re_allocate();
};

/// Реализация методов шаблонного класса
template <typename TElem>
FPTArray<TElem>::FPTArray(size_t arr_sz) :
    data_{new TElem[arr_sz]}, length_{arr_sz}, capacity_{arr_sz}
{}

template <typename TElem>
FPTArray<TElem>::~FPTArray()
{
    delete[] data_;
    data_ = nullptr;
}

template <typename TElem>
FPTArray<TElem>::FPTArray(const FPTArray<TElem>& other) :
    data_{new TElem[other.capacity_]}, length_{other.length_},
    capacity_{other.capacity_}
{
    for (size_t i = 0; i < other.length_; i++) {
        data_[i] = other.data_[i];
    }
}

template <typename TElem>
FPTArray<TElem>::FPTArray(FPTArray<TElem>&& other) :
    data_{other.data_}, length_{other.length_}, capacity_{other.capacity_}
{
    other.data_ = nullptr;
    other.length_ = other.capacity_ = 0;
}

template <typename TElem>
TElem& FPTArray<TElem>::operator[](size_t index)
{
    const size_t safe_index = (length_ == 0) ? 0 : index % length_;
    return data_[safe_index];
}

template <typename TElem>
const TElem& FPTArray<TElem>::operator[](size_t index) const
{
    const size_t safe_index = (length_ == 0) ? 0 : index % length_;
    return data_[safe_index];
}

template <typename TElem>
FPTArray<TElem>& FPTArray<TElem>::operator=(const FPTArray<TElem>& rhs)
{
    if (this == &rhs) {
        return *this;
    }

    delete[] data_;

    length_ = rhs.length_;
    capacity_ = rhs.capacity_;

    data_ = new TElem[capacity_];
    for (size_t i = 0; i < rhs.length_; i++) {
        data_[i] = rhs.data_[i];
    }

    return *this;
}

template <typename TElem>
FPTArray<TElem>& FPTArray<TElem>::operator=(FPTArray<TElem>&& rhs)
{
    std::swap(data_, rhs.data_);
    std::swap(length_, rhs.length_);
    std::swap(capacity_, rhs.capacity_);

    return *this;
}

template <typename TElem>
TElem FPTArray<TElem>::back() const
{
    const int idx = length_ == 0 ? 0 : length_ - 1;
    return data_[idx];
}

template <typename TElem>
TElem FPTArray<TElem>::front() const
{
    return data_[0];
}

template <typename TElem>
TElem FPTArray<TElem>::pop()
{
    const int idx = length_ == 0 ? 0 : length_ - 1;
    const TElem deleted = data_[idx];

    if (length_ != 0) {
        length_ -= 1;
    }

    return deleted;
}

template <typename TElem>
size_t FPTArray<TElem>::length() const
{
    return length_;
}

template <typename TElem>
void FPTArray<TElem>::push(const TElem& new_elem)
{
    if (length_ >= capacity_) {
        re_allocate();
    }

    data_[length_] = new_elem;
    length_++;
}

template <typename TElem>
void FPTArray<TElem>::re_allocate()
{
    capacity_ = (capacity_ == 0) ? 2 : capacity_ * 2;

    TElem *new_data = new TElem[capacity_];
    for (size_t i = 0; i < length_; i++) {
        new_data[i] = data_[i];
    }

    delete[] data_;
    data_ = new_data;
}

template <typename TElem>
TElem* FPTArray<TElem>::begin()
{
    return data_;
}

template <typename TElem>
TElem* FPTArray<TElem>::end()
{
    return data_ + length_;
}

template <typename TElem>
const TElem* FPTArray<TElem>::begin() const
{
    return data_;
}

template <typename TElem>
const TElem* FPTArray<TElem>::end() const
{
    return data_ + length_;
}
#endif
