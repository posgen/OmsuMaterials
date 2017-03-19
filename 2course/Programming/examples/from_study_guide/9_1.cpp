/*
    В программе ввести и инициализировать массив структур, каждая из которых
    описывает материальную точку. Элементы структурного типа: координаты и
    массы частиц, а также расстояния от центра масс до всех точек набора.
    Окончание ввода - ннулевое значение массы точки.

    Общая масса системы точек M = sum_{i} m_i, где под m_i обозначена масса
    отдельных точек.
    Координаты центра масс: x_c = sum_{i} (x_i * m_i) / M,
    y_c = sum_{i} (y_i * m_i) / M, z_c = sum_{i} (z_i * m_i) / M
    (x_i, y_i, z_i) - координаты отдельных точек.

    Расстояние до центра масс определяется как:
        r_i = sqrt( (x_i - x_c)^2 + (y_i - y_c)^2 + (z_i - z_c)^2 )

    Версия для С++, но с использованием realloc / free для выделение памяти под массив простых структур.
*/

#include <iostream>
#include <cstdlib>
#include <clocale> // установка вывода русских букв в командную строку (больше нужна для Windows OS)
#include <cmath>

using namespace std;

struct MassPoint {
    double coord[3];
    double mass;
};

struct PointSet {
    struct MassPoint m_point;
    double distance;
};


int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "RUS");

    int i, count = 0;
    double rx, ry, rz;

    struct PointSet mass_center = { {0., 0., 0., 0.}, 0. };
    struct PointSet next_point;
    struct PointSet *p_array = nullptr;

    cout << "Введите точки (порядок ввода: масса, координата x, координата y, координата z).\nПоставьте 0 в качестве массы для прекращения задания точек" << endl;

    while ( true ) {
        cout << "Точка номер " << (count + 1) << endl << "\tмасса: ";
        cin >> next_point.m_point.mass;

        if ( next_point.m_point.mass < 0.0000000001 )
            break;

        cout << "\tкоординаты (3 значения через пробел): ";
        cin >> next_point.m_point.coord[0] >> next_point.m_point.coord[1] >> next_point.m_point.coord[2];

        count++;

        p_array = (struct PointSet *) realloc(p_array, count * sizeof(struct PointSet));
        if (p_array == nullptr) {
            cerr << "Проблема с выделением дополнительно памяти\n";
            return -1;
        }
        p_array[count - 1] = next_point;

        mass_center.m_point.mass += next_point.m_point.mass;
        mass_center.m_point.coord[0] += next_point.m_point.coord[0] * next_point.m_point.mass;
        mass_center.m_point.coord[1] += next_point.m_point.coord[1] * next_point.m_point.mass;
        mass_center.m_point.coord[2] += next_point.m_point.coord[2] * next_point.m_point.mass;
    }

    mass_center.m_point.coord[0] /= mass_center.m_point.mass;
    mass_center.m_point.coord[1] /= mass_center.m_point.mass;
    mass_center.m_point.coord[2] /= mass_center.m_point.mass;

    cout << "Итоги." << endl;
    cout << "Центр масс: " << endl;
    cout << "\tмасса = " << mass_center.m_point.mass << ", координаты = {" << mass_center.m_point.coord[0] <<
            ", " << mass_center.m_point.coord[1] <<
            ", " << mass_center.m_point.coord[2] << "}" << endl;

    cout << "\nВведённые точки:" << endl;
    for (i = 0; i < count; i++) {
        rx = p_array[i].m_point.coord[0] - mass_center.m_point.coord[0];
        ry = p_array[i].m_point.coord[1] - mass_center.m_point.coord[1];
        rz = p_array[i].m_point.coord[2] - mass_center.m_point.coord[2];

        p_array[i].distance = sqrt(rx*rx + ry*ry + rz*rz);

        cout << "Точка номер " << i + 1  << ", координаты: {" << p_array[i].m_point.coord[0] <<
            ", " << p_array[i].m_point.coord[1] <<
            ", " << p_array[i].m_point.coord[2] <<
            "}\n\tмасса = " << p_array[i].m_point.mass << ", расстояние до ц.м. = " << p_array[i].distance << endl;
    }

    free(p_array);

    return 0;
}
