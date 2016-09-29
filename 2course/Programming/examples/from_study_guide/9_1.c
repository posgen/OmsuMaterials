/*
    В программе ввести и инициализировать массив структур, каждая из которых
    описывает материальную точку. Элементы структурного типа: координаты и
    массы частиц, а также расстояния от центра масс до всех точек набора.
    Окончание ввода - нулевое значение массы точки.

    Общая масса системы точек M = sum_{i} m_i, где под m_i обозначена масса
    отдельных точек.
    Координаты центра масс: x_c = sum_{i} (x_i * m_i) / M,
    y_c = sum_{i} (y_i * m_i) / M, z_c = sum_{i} (z_i * m_i) / M (x_i, y_i, z_i) -
    координаты отдельных точек.

    Расстояние до центра масс определяется как:
        r_i = sqrt( (x_i - x_c)^2 + (y_i - y_c)^2 + (z_i - z_c)^2 )
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h> // установка русской локали (нужна для ОС Windows)

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
    struct PointSet *p_array = NULL;

    printf("Введите материальные точки (порядок ввода: масса, x, y, z).\nВведите нулевую массу для прекращения ввода точек.\n");

    while (1) {
        printf("Точка номер %d\n", count + 1);
        scanf("%le", &next_point.m_point.mass);
        if ( next_point.m_point.mass < 0.0000000001 )
            break;

        scanf("%le", &next_point.m_point.coord[0]);
        scanf("%le", &next_point.m_point.coord[1]);
        scanf("%le", &next_point.m_point.coord[2]);

        count++;

        p_array = (struct PointSet *) realloc(p_array, count * sizeof(struct PointSet));
        if (p_array == NULL) {
            perror("Ошибка выделения памяти");
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

    puts("Результат:");
    puts("Центр масс: ");
    printf("масса = %lf, координаты = {%lf, %lf, %lf}\n", mass_center.m_point.mass,
            mass_center.m_point.coord[0], mass_center.m_point.coord[1], mass_center.m_point.coord[2]);

    puts("Points:");
    for (i = 0; i < count; i++) {
        rx = p_array[i].m_point.coord[0] - mass_center.m_point.coord[0];
        ry = p_array[i].m_point.coord[1] - mass_center.m_point.coord[1];
        rz = p_array[i].m_point.coord[2] - mass_center.m_point.coord[2];

        p_array[i].distance = sqrt(rx*rx + ry*ry + rz*rz);

        printf("Точка номер %d, координаты: {%lf, %lf, %lf}\n\tмасса = %lf, расстояние от центра масс = %lf\n",
            i + 1, p_array[i].m_point.coord[0], p_array[i].m_point.coord[1], p_array[i].m_point.coord[2],
            p_array[i].m_point.mass, p_array[i].distance);
    }

    free(p_array);
    return 0;
}
