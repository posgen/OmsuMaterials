#include <stdio.h>
#include <stdlib.h>

#include <windows.h>

unsigned long binom_coef(unsigned n, unsigned k)
{
    if ( k > n ) {
        return 0;
    }

    unsigned long result = 1;

    unsigned tmp = n - k + 1;
    while ( tmp <= n ) {
        result *= tmp;
        ++tmp;
    }

    tmp = 2;
    while ( tmp <= k ) {
        result /= tmp;
        ++tmp;
    }

    return result;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("Разложение (x + y)^n\n");
    printf("Введите n = ");

    unsigned n;
    scanf("%u", &n);
    if ( k == 0 ) {
        printf("x^%u ", n);
    }

    if ( k == n ) {
        printf("y^%u ", n);
    }
    printf("(x + y)^%u = ", n);

    unsigned long bnm;
    for (unsigned k = 0; k <= n; ++k) {
        if ( k == 0 ) {
            printf("x^%u ", n);
            continue;
        }

        if ( k == n ) {
            printf(" + y^%u ", n);
            continue;
        }

        bnm = binom_coef(n, k);
        printf(" + %lu(x^%u)(y^%u)", bnm, n - k, k);
    }
    printf("\nВсё получилось!");
}
