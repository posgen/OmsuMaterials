/**
    Программа для поиска email'ов среди введённого текста.

    По идее, 14 строк (60 - 73) - это всё, что надо было добавить самостоятельно.
*/

#include "ffhelpers.h"

using namespace std;
using namespace ffomsu;

bool is_email(string word)
{
    size_t pos_at = word.find("@");
    if (pos_at == string::npos){
        return false;
    }

    size_t pos_dot = word.find(".", pos_at);
    if (pos_dot == string::npos or
        pos_dot == word.length() - 1 or
        pos_dot == pos_at + 1) {
        return false;
    }

    return true;
}


int main()
{
    string text;
    print("Введите текст построчно (для окончания - введите строку 'stop.')\n");
    /**
        Немного переделанный ввод текста. Слова можно вводить в любом порядке, хоть построчно,
        хоть нет. Как только в отдельной строке набираем слово *stop* - ввод текста прекращается.

        Технически используется бесконечный цикл (do {...} while ( true )).

        Предыдущий задуманный вариант с разделителем точкой (getline(..., ..., '.')) - не очень хорош
        для данной задачи.
    */
    do {
        string predl;
        getline(cin, predl);

        if (predl == "stop") {
            break;
        }

        /// Данным if-ом сохраняем текст со всеми переносами.
        if (text != "") {
            text += '\n';
        }

        text += predl;
    } while ( true );

    /// Цикл разиения всего текста на слова и проверка каждого из них (email or not).
    for (size_t i = 0, start_pos = 0; i < text.length(); i++) {
        if (text[i] == ' ' or text[i] == '\n' or (i == text.length() - 1)) {
            string slovo = text.substr(start_pos, i - start_pos);

            /// Если слово не является пустой строкой
            if (slovo != "") {
                if (is_email(slovo)) {
                    print("Слово #", slovo, "# является email'ом\n");
                }
            }

            start_pos = i + 1;
        }
    }
}
