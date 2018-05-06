/**
    Пример класса SafetyArray из 8-ой лекции
*/

#include <algorithm>  /// используем функцию copy_n для копирования элементов одного массива в другой
#include <iostream>   /// вывод на консоль
#include <cstdlib>    /// нужна для правильного выбора функции abs
#include <cmath>      /// причина аналогична выше

class SafetyArray
{
public:
    SafetyArray();                         /// конструктор раз
    SafetyArray(size_t sz);                /// конструктор два
    SafetyArray(size_t sz, double value);  /// конструктор три

    ~SafetyArray(); /// деструктор

    double elem_at(int index) const;
    size_t length() const;

    SafetyArray& push_to_end(double new_value);
    SafetyArray& set_at(int index, double value);

    SafetyArray& operator=(const SafetyArray& rhs);
    friend std::ostream& operator<<(std::ostream&, const SafetyArray&);

private:
    double *_arr;
    size_t _length;
    size_t _capacity;

    size_t compute_index(int index) const;
};

int main()
{
    SafetyArray my_test_arr; // создаём массив

    // заполняем первые 4 элемента
    my_test_arr.push_to_end(4.5).push_to_end(7.89)
        .push_to_end(0.555).push_to_end(-8.4);

    std::cout << "Длина массива: " << my_test_arr.length()
         << "\nЕго элементы:\n[";
    for (size_t i = 0; i < my_test_arr.length(); ++i) {
        if (i != 0) {
            std::cout << ", ";
        }

        std::cout << my_test_arr.elem_at(i);
    }
    std::cout << "]\n";

    SafetyArray arr1, arr2;

    arr1.push_to_end(555.5);
    arr1.push_to_end(9.992);

    arr2 = arr1;
    arr2.set_at(1, 6.78); // устанавливаем второй элемент

    std::cout << "Второй элемент массива arr1: " << arr1 << "\n";
    std::cout << "Второй элемент массива arr2: " << arr2 << "\n";

    SafetyArray arr3, arr4{16}, arr5{20, 4.4};
    std::cout << arr3 << "\n\n"
              << arr4 << "\n\n"
              << arr5 << "\n\n";
}

SafetyArray::SafetyArray() :
    _arr{new double[4]}, _length{0}, _capacity{4}
{}

SafetyArray::SafetyArray(size_t sz) :
    _arr{new double[sz]}, _length{0}, _capacity{sz}
{}

SafetyArray::SafetyArray(size_t sz, double value) :
    _arr{new double[sz]}, _length{sz}, _capacity{sz}
{
    for (size_t i = 0; i < sz; ++i) {
        _arr[i] = value;
    }
}

SafetyArray::~SafetyArray()
{
    delete[] _arr;
}

size_t SafetyArray::length() const
{
    return _length;
}

SafetyArray& SafetyArray::push_to_end(double new_value)
{
  if ( _length < _capacity ) {
    _arr[_length] = new_value;
  } else {
  	_capacity *= 2;
  	double *new_arr = new double[_capacity];
  	for (size_t i = 0; i < _length; ++i) {
  	  new_arr[i] = _arr[i];
  	}
  	new_arr[_length] = new_value;
  	delete[] _arr;
  	_arr = new_arr;
  }

  ++_length;
  return *this;
}

size_t SafetyArray::compute_index(int index) const
{
  if (index == 0) {
    return 0;
  } else if (index > 0) {
    return std::abs(index) % _length;
  }

  size_t rel_index = std::abs(index) % _length;
  if (rel_index == 0) {
    return 0;
  }

  return std::abs(_length - rel_index);
}

double SafetyArray::elem_at(int index) const
{
  if (_length == 0) {
    return std::nan("");
  }

  return _arr[ compute_index(index) ];
}

SafetyArray& SafetyArray::set_at(int index, double value)
{
  if (_length != 0) {
	_arr[ compute_index(index) ] = value;
  }

  return *this;
}

SafetyArray& SafetyArray::operator=(const SafetyArray& rhs)
{
  if (this != &rhs) {
	delete[] _arr;
	_length   = rhs._length;
	_capacity = rhs._capacity;

	_arr = new double[_length];
	std::copy_n(rhs._arr, _length, _arr);
  }

  return *this;
}

std::ostream& operator<<(std::ostream& os, const SafetyArray& rhs)
{
  os << "{Длина: " << rhs.length() << ", ёмкость: "
     << rhs._capacity << "\n";

  os << "[";
  for (size_t i = 0; i < rhs.length(); ++i) {
    if (i != 0) { os << ", "; }

    os << rhs.elem_at(i);
  }
  os << "]}";

  return os;
}
