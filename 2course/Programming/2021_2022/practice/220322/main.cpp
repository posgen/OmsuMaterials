#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>

#include "fptarray.h"

int main()
{
    FPTArray<std::string> words = {
        "Один",
        "Два",
        "Три",
        "diphosgen"
    };

    std::cout << words[3] << std::endl;

    FPTArray<double> rates = {4.5, 1.4, 5.6, 9.8, 7.85, 4.5};
    for (double& rate : rates) {
        rate *= 0.7;
    }

    for (const double& rate : rates) {
        std::cout << rate << ' ';
    }
    std::cout << std::endl;

    /** accumulate прячется в <numeric>

        поставьте третьим аргументом <<0>> вместо <<0.0>>
        и попробуйте пояснить, почему результат поменяется.
    */
    double sum = std::accumulate(rates.begin(), rates.end(), 0.0);
    std::cout << "Sum of rates elements is " << sum << std::endl;

    const FPTArray<int> numbers = {5, -4, 8, -23, 19, 16, 12, 4, 5, 2};
    for (const int numb : numbers) {
        std::cout << numb << ", ";
    }
    std::cout << std::endl;

    /// вспомним и про анонимные функции
    int even_count = std::count_if(numbers.begin(), numbers.end(), [](int i) { return i % 2 == 0; });
    std::cout << "numbers has " << even_count << " even items" << std::endl;
}
