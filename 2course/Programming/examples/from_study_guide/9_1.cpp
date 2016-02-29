/*
    В программе ввести и инициализировать массив структур, каждая из которых
    описывает материальную точку. Элементы структурного типа: координаты и
    массы частиц, а также расстояния от центра масс до всех точек набора.
    Окончание ввода - ннулевое значение массы точки.

    Общая масса системы точек M = sum_{i} m_i, где под m_i обозначена масса
    отдельных точек.
    Координаты центра масс: x_c = sum_{i} (x_i * m_i) / M,
    y_c = sum_{i} (y_i * m_i) / M, z_c = sum_{i} (z_i * m_i) / M (x_i, y_i, z_i) -
    координаты отдельных точек.

    Расстояние до центра масс определяется как:
        r_i = sqrt( (x_i - x_c)^2 + (y_i - y_c)^2 + (z_i - z_c)^2 )

    Версия для С++, но с использованием realloc / free для выделение памяти под массив простых структур.
*/

#include <iostream>
#include <cstdlib>
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
    int i, count = 0;
    double rx, ry, rz;

    struct PointSet mass_center = { {0., 0., 0., 0.}, 0. };
    struct PointSet next_point;
    struct PointSet *p_array = NULL;

    cout << "Enter the points (order: mass, x, y, z). Enter 0 mass to stop" << endl;

    while ( true ) {
        cout << "Point number " << (count + 1) << endl << "\tmass: ";
        cin >> next_point.m_point.mass;

        if ( next_point.m_point.mass < 0.0000000001 )
            break;

        cout << "\tcoords:" << endl;
        cin >> next_point.m_point.coord[0] >> next_point.m_point.coord[1] >> next_point.m_point.coord[2];

        count++;

        p_array = (struct PointSet *) realloc(p_array, count * sizeof(struct PointSet));
        if (p_array == NULL) {
            cerr << "Realocation memory error";
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

    cout << "Result:" << endl;
    cout << "Mass center: " << endl;
    cout << "mass = " << mass_center.m_point.mass << ", coords = {" << mass_center.m_point.coord[0] <<
            ", " << mass_center.m_point.coord[1] <<
            ", " << mass_center.m_point.coord[2] << endl;

    cout << "Points:" << endl;
    for (i = 0; i < count; i++) {
        rx = p_array[i].m_point.coord[0] - mass_center.m_point.coord[0];
        ry = p_array[i].m_point.coord[1] - mass_center.m_point.coord[1];
        rz = p_array[i].m_point.coord[2] - mass_center.m_point.coord[2];

        p_array[i].distance = sqrt(rx*rx + ry*ry + rz*rz);

        cout << "Number " << i + 1  << ", coord: {" << p_array[i].m_point.coord[0] <<
            ", " << p_array[i].m_point.coord[1] <<
            ", " << p_array[i].m_point.coord[2] <<
            "}\n\tmass = " << p_array[i].m_point.mass << ", distance = " << p_array[i].distance << endl;
    }

    free(p_array);
    return 0;
}
