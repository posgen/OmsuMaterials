#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <locale>
#include <vector>
#include <string>
#include <cmath>

/**
    Первая часть работы со временем в C++.

    Использование <ctime>.
*/

using namespace std;

double operator""_deg(long double degree)
{
    return degree * M_PI / 180.0;
}

double operator""_deg(unsigned long long degree)
{
    return double(degree) * M_PI / 180.0;
}

int main()
{
    time_t ttt;
    time_t tt = time(&ttt);
    cout << tt << " seconds from epoch ("
         << ttt << ")" << endl;

    time_t tm2 = tt - 3600 * 10;
    tm tm_pt1 = *localtime(&tm2);
    tm tm_pt2 = *gmtime(&tm2);

    /**
        Локали приведены для ОС на основе Linux.
        Чтобы всё работало, язык должен быть добавлен в операционную систему.

        На ОС семейства Windows названия локалей будут другие. Их надо смотреть
        где-то в "региональных настройках" ("Region and language settings", точное
        название в русскоязычном интерфейсе - не помню). Для примера, интернет говорит
        о том, что локаль для французкого языка, канадского диалекта, назвается -
        "French_Canada.1252". Проверить, как она называется для русского языка можно
        попробывать следующим кодом:
            std::locale::global("");
            std::cout << std::locale().name() << std::endl;

        Если названия разных локалей будут обнаружены и установлены в Вашей ОС,
        то их следует добавить в массив локалей ниже, убрав линукс-специфичные.
    */
    for (const char* lcl : {"C", "ru_RU.utf8", "ja_JP.utf8"}) {
        auto lcl_obj = locale(lcl);
        locale::global(lcl_obj);
        cout.imbue(lcl_obj);
        cout << "current locale: " << lcl << endl;

        cout << "tm_pt1 as str: "
             << put_time(&tm_pt1, "%Y--%m--%d %T (%W, %b, %B)")
             << endl;

        char buf[128];
        strftime(buf, 128, "%Y--%m--%d %T (%W, %b, %B)", &tm_pt2);
        cout << "tm_pt2 as str: " << buf << endl
             << "=========================\n\n";
    }

    auto tt_diff = time(nullptr) - tt;
    cout << "program elapsed: " << tt_diff << "seconds" << endl;

    cout << "sin(30) = " << sin(-30_deg) << endl;
    cout << "cos(45) = " << cos(-45_deg) << endl;
}
