#include "liblect5.h"

#include <algorithm>

FP003Array::FP003Array(size_t arr_sz) :
    data_{new int[arr_sz]}, length_{arr_sz}, capacity_{arr_sz}
{}

FP003Array::~FP003Array()
{
    delete[] data_;
    data_ = nullptr;
}

FP003Array::FP003Array(const FP003Array& other) :
    data_{new int[other.capacity_]}, length_{other.length_}, capacity_{other.capacity_}
{
    for (size_t i = 0; i < other.length_; i++) {
        data_[i] = other.data_[i];
    }
}

FP003Array::FP003Array(FP003Array&& other) :
    data_{other.data_}, length_{other.length_}, capacity_{other.capacity_}
{
    other.data_ = nullptr;
    other.length_ = other.capacity_ = 0;
}

int& FP003Array::operator[](size_t index)
{
    const size_t safe_index = (length_ == 0) ? 0 : index % length_;
    return data_[safe_index];
}

const int& FP003Array::operator[](size_t index) const
{
    const size_t safe_index = (length_ == 0) ? 0 : index % length_;
    return data_[safe_index];
}

FP003Array& FP003Array::operator=(const FP003Array& rhs)
{
    if (this == &rhs) {
        return *this;
    }

    delete[] data_;

    length_ = rhs.length_;
    capacity_ = rhs.capacity_;

    data_ = new int[capacity_];
    for (size_t i = 0; i < rhs.length_; i++) {
        data_[i] = rhs.data_[i];
    }

    return *this;
}

/*
// первая реализация
FP003Array& FP003Array::operator=(FP003Array&& rhs)
{
    delete[] data_;

    data_ = rhs.data_;
    length_ = rhs.length_;
    capacity_ = rhs.capacity_;

    rhs.data_ = nullptr;
    rhs.length_ = rhs.capacity_ = 0;

    return *this;
}
*/

// реализация, исключающая операцию удаления
FP003Array& FP003Array::operator=(FP003Array&& rhs)
{
    std::swap(data_, rhs.data_);
    std::swap(length_, rhs.length_);
    std::swap(capacity_, rhs.capacity_);

    return *this;
}


int FP003Array::back() const
{
    const int idx = length_ == 0 ? 0 : length_ - 1;
    return data_[idx];
}

int FP003Array::front() const
{
    return data_[0];
}

int FP003Array::pop()
{
    const int idx = length_ == 0 ? 0 : length_ - 1;
    const int deleted = data_[idx];

    if (length_ != 0) {
        length_ -= 1;
    }

    return deleted;
}

size_t FP003Array::length() const
{
    return length_;
}

void FP003Array::push(int new_elem)
{
    if (length_ >= capacity_) {
        re_allocate();
    }

    data_[length_] = new_elem;
    length_++;
}

void FP003Array::re_allocate()
{
    capacity_ = (capacity_ == 0) ? 2 : capacity_ * 2;

    int *new_data = new int[capacity_];
    for (size_t i = 0; i < length_; i++) {
        new_data[i] = data_[i];
    }

    delete[] data_;
    data_ = new_data;
}

FP003Array::Iterator FP003Array::begin()
{
    return Iterator(0, *this);
}

FP003Array::Iterator FP003Array::end()
{
    return Iterator(length_, *this);;
}

FP003Array::Iterator::Iterator(size_t idx, FP003Array& obj) :
    index{idx}, arr_ref{obj}
{}

bool FP003Array::Iterator::operator!=(const FP003Array::Iterator& rhs)
{
    return index != rhs.index;
}

FP003Array::Iterator& FP003Array::Iterator::operator++()
{
    index++;
    return *this;
}

int& FP003Array::Iterator::operator*()
{
    return arr_ref.data_[index];
}
