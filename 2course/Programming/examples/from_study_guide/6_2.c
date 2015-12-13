/*
    Ввести с клавиатуры в виде одной строки арифметическое выражение, включающее 2 положительных целых
    и знак одной из 4-х арифметических операций (+, -, *, /), размещённых между ними, и вычислить значение выражения
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 99
#define OP_SIZE 9

int main()
{
    char expression[SIZE];
    char op_left[OP_SIZE], op_right[OP_SIZE]; // левый и правый операнды выражения
    char operation, *beg;
    char numbers[] = "0123456789";
    int len, result, value_left, value_right;

    printf("Enter the expression:\n");
    fgets(expression, SIZE, stdin);

    beg = strpbrk(expression, numbers);
    len = strspn(beg, numbers);
    strncpy(op_left, beg, len);
    op_left[len] = '\0';
    value_left = atoi(op_left);

    beg = strpbrk(beg, "+-*/");
    operation = *beg;

    beg = strpbrk(beg, numbers);
    len = strspn(beg, numbers);
    strncpy(op_right, beg, len);
    op_right[len] = '\0';
    value_right = atoi(op_right);

    switch(operation) {
        case '+':
            result = value_left + value_right;
            break;
        case '-':
            result = value_left - value_right;
            break;
        case '*':
            result = value_left * value_right;
            break;

        case '/':
            if (value_right != 0)
                result = value_left / value_right;
            else {
                printf("Error! Division by zero\n");
                return 1;
            }
            break;
        default:
            printf("Invalid operation\n");
            return 1;
    }

    printf("The expression is:\n%s %c %s = %d\n", op_left, operation, op_right, result);
    return 0;
}
