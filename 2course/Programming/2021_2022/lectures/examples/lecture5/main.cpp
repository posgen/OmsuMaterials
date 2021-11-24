#include <algorithm>
#include <iostream>
#include <utility>

#include "liblect5.h"

void pretty_print(const FP003Array);
void init_by_squares(FP003Array&);
FP003Array make_array(size_t array_size, int start, int step);
void swap_array(FP003Array& lhs, FP003Array& rhs);

int main()
{
    using namespace std;

    FP003Array examp1{10};

    examp1[0] = 4;
    examp1[3] = -5;
    cout << "Length: " << examp1.length() << endl;
    cout << "Fourth elem: "<< examp1[3] << endl;

    examp1.push(45);
    cout << "Length: " << examp1.length() << endl;

    FP003Array examp2{20};
    init_by_squares(examp2);
    pretty_print(examp2);

    FP003Array examp3 = examp1;
    examp3[0] *= 4;
    examp3[1] = -3;
    examp3[5] = 9;
    pretty_print(examp3);

    FP003Array examp4 = FP003Array(7);
    init_by_squares(examp4);
    cout << "Размер examp4 = " << examp4.length() << endl;

    cout << "Before\nexamp3 contains:\n";
    pretty_print(examp3);
    cout << "examp4 contains:\n";
    pretty_print(examp4);
    cout << "====================\n";
    swap_array(examp3, examp4);

    cout << "After\nexamp3 contains:\n";
    pretty_print(examp3);
    cout << "examp4 contains:\n";
    pretty_print(examp4);

    FP003Array examp5 = make_array(8, 40, 2);
    pretty_print(examp5);

    string str = "A simple string";
    for (string::iterator it = str.begin(); it != str.end(); it++) {
        const char symb = *it;
        if (symb != ' ') {
            cout << '{' << symb << '}';
        }
    }
    cout << endl;

    for (int elem : examp4) {
        cout << "<<" << elem << ">>";
    }
    cout << endl;

    //std::sort(examp4.begin(), examp4.end());
    //7pretty_print(examp4);
}

void pretty_print(const FP003Array obj)
{
    std::cout << "[";
    const size_t len = obj.length();

    for (size_t i = 0; i < obj.length(); i++) {
        const auto extra_str = (i == (len - 1)) ? "" : ", ";
        std::cout << obj[i] << extra_str;
    }
    std::cout << "]" << std::endl;
}

void init_by_squares(FP003Array& obj)
{
    for (size_t i = 0; i < obj.length(); i++) {
        obj[i] = i * i;
    }
}

FP003Array make_array(size_t array_size, int start, int step)
{
  FP003Array new_obj{array_size};

  for (size_t i = 0; i < new_obj.length(); i++) {
    new_obj[i] = start + i * step;
  }

  return new_obj;
}

void swap_array(FP003Array& lhs, FP003Array& rhs)
{
    FP003Array tmp = std::move(lhs);
    lhs = std::move(rhs);
    rhs = std::move(tmp);
}

