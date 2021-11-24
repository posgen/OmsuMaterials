#ifndef LIBLECT3_INCLUDED
#define LIBLECT3_INCLUDED

#include <cstddef>

class FP003Array
{
public:
    FP003Array() = default;
    FP003Array(size_t arr_sz);
    FP003Array(const FP003Array& other);
    // параметр - ссылка на временный объект (либо - rvalue)
    FP003Array(FP003Array&& other);

    ~FP003Array();

    FP003Array& operator=(const FP003Array& rhs);
    FP003Array& operator=(FP003Array&& rhs);

    int& operator[](size_t index);
    // Специальная перегрузка для возможности использования констант
    // данного типа (как напрямую, так и в качестве параметров функций)
    const int& operator[](size_t index) const;

    int back() const;         // new
    int front() const;        // new
    size_t length() const;
    int pop();                // new
    void push(int new_elem);

    class Iterator
    {
    public:
        Iterator(size_t idx, FP003Array& obj);

        bool operator!=(const Iterator& rhs);
        Iterator& operator++();
        int& operator*();

    private:
        size_t index;
        FP003Array& arr_ref;
    };

    Iterator begin();
    Iterator end();

private:
    int *data_ = nullptr;
    size_t length_ = 0;
    size_t capacity_ = 0;

    void re_allocate();
};

#endif
