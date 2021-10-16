#include <iostream>

#include "liblect3.h"

void pretty_print(const FP003Array);
void init_by_squares(FP003Array&);

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
