#include "ffhelpers.h"

using namespace ffomsu;

int main()
{
    print("enter function number: \n");
    print("1 --> sin\n2 --> cos\n");
    print("3 --> tg\n4 --> arcsin\n");
    print("5 --> arccos\n");
    int nfunc;
    get_value(nfunc);

    double arg;
    get_value(arg, "enter argument: ");

    switch (nfunc) {
    case 1:
        print("sin(", arg, ") = ", sin(arg));
        break;
    case 2:
        print("cos(", arg, ") = ", cos(arg));
        break;
    case 3:
        print("tg(", arg, ") = ", tan(arg));
        break;
    case 4:
        print("arcsin(", arg, ") = ", asin(arg));
        break;
    case 5:
        print("arccos(", arg, ") = ", acos(arg));
        break;
    default:
        print("function number is invalid");
    }
}
