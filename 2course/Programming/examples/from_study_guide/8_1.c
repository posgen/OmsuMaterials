/*
    Написать программу регистрации и обработки наблюдений за ежедневной температурой воздуха.
    При запуске программы запрашивается дата и температура. После ввода данных для одного
    дня, информация сохраняется в файл и выдаётся справка о средней температуре за весь период
    наблюдения.
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h> // установка русской локали (нужна для ОС Windows)

// Проверка правильности введённой даты
int is_valid_date(int day, int month, int year)
{
    int max_days_in_month[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int max_day;

    if ( year < 0)
        return 0;
    if ( month < 1 || month > 12 )
        return 0;

    if ( (month != 2) || (year % 4 == 0) ) {
        max_day = max_days_in_month[month - 1];
    } else {
        max_day = 28;
    }

    if (day < 1 || day > max_day)
        return 0;

    return 1;
}

int main()
{
    setlocale(LC_ALL, "RUS");

    int i, sum, day, month, year, temperature;
    FILE *file_pointer;
    char *file_name = "temperature";

    do {
        printf("\nВведите дату день/месяц/год (слэш - разделитель): ");
        scanf("%d/%d/%d", &day, &month, &year);
    } while ( !is_valid_date(day, month, year) );

    do {
        printf("\nВведите температуру (в диапазоне [-100; 80]): ");
        scanf("%d", &temperature);
    } while ( temperature < -100 || temperature > 80 );

    printf("\nСохранение данных...");
    file_pointer = fopen(file_name, "a");
    if ( file_pointer == NULL ) {
        perror("Невозможно открыть файл для записи");
        return -1;
    }

    fprintf(file_pointer, "%d %d %d %d\n", day, month, year, temperature);
    fclose(file_pointer);

    printf("\nЗагрузка данных...");
    file_pointer = fopen(file_name, "r");
    if ( file_pointer == NULL ) {
        perror("Невозможно открыть файл для чтения");
        return -1;
    }

    for (i = 0, sum = 0; !feof(file_pointer); i++) {
        fscanf(file_pointer, "%d %d %d %d", &day, &month, &year, &temperature);
        sum += temperature;
    }
    fclose(file_pointer);

    printf("\nСреднее значение температуры: %lf", (double) sum / i);

    return 0;
}
