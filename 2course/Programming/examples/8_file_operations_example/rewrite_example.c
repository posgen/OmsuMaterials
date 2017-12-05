/*
    Пример перезаписи в выходном потоке.
    Оригинал на C++ тут: http://www.cplusplus.com/reference/ostream/ostream/seekp/
    С-версия
*/

#include <stdio.h>
#include <stdlib.h>

int main() 
{
    FILE *out_stream = fopen("example_rewriting.txt", "w");

    if (out_stream != NULL) {
        const char phrase[] = "This is an apple.";
        fputs(phrase, out_stream);
        
        long position = ftell(out_stream);
        fseek(out_stream, position - 8, SEEK_SET);
        fprintf(out_stream, "%4s", " sam");

        fclose(out_stream);
        // В итоге в файле окажется строка: "This is a sample"

        printf("Запись завершена\n");
    } else {
        perror("Ошибка открытия файла");
    }
}
