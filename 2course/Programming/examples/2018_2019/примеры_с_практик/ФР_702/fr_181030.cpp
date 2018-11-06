/**
    Программа для поиска email'ов среди введённого текста.

    Проверка почтового адреса - реализована, осталось разбить
    введённый текст на слова и проверить каждое из них.

    Самая простая и производительная идея для разбиения заключается в
    следующем:
        * заводим две переменные для позиций - для запоминания начала слова и его окончания:
        * одной из них присваиваем, условно pos_start = 0;
        * посимвольно идём по строке и ищем либо символ пробела(' '), либо символ '\n';
        * как только пробел найден - применяем метод получения фрагмента:
            text.substr(pos_start, pos_end - pos_start)
            pos_end - позиция найденного пробела
        * далее pos_start = pos_end + 1 и продолжаем поиск по тексту следующего слова.
*/

#include "ffhelpers.h"

using namespace std;
using namespace ffomsu;

bool proverka_na_email(string slovo)
{
    size_t poz = slovo.find("@");
    if (poz == string::npos){
        return false;
    }

    size_t pos = slovo.find(".", poz);
    if (pos == string::npos or
        pos == slovo.length() - 1 or
        pos == poz + 1) {
        return false;
    }

    return true;
}


int main()
{
    string text;

    size_t kol_vo;
    get_value(kol_vo, "введите количество предложений");
    for (size_t i = 1; i <= kol_vo; i++ ) {
        string predl;
        getline(cin, predl, '.');
        text += predl;
    }

}
