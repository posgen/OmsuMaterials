/**
    Представляем некоторую геометрическую фигуру в виде массива точек.
    И поворачиваем её вокруг оси Oz на заданный угол.
*/

#include "ffhelpers.h"

using namespace std;
using namespace ffomsu;

const size_t MAX_POINTS=100;

int main()
{
    show_rus_letters();
    int array_points[MAX_POINTS][3];
    size_t points_count;
    get_value(points_count, "Введите число точек: ");
    if (points_count > MAX_POINTS) {
        print("Введённое кол-во точек превышает максимально допустимый размер");
        return 0;
    }

    for (size_t i = 0; i < points_count; i++) {
        array_points[i][0] = rand_a_b_incl(-8, 10);
        array_points[i][1] = rand_a_b_incl(-8, 10);
        array_points[i][2] = rand_a_b_incl(-8, 10);

    }

    int angle;
    get_value(angle,"Введите угол поворота (в градусах): ");
    double rotate_matrix_z[3][3] = {
        {cos(angle *  (M_PI/180)), -sin(angle * (M_PI/180)), 0.0},
        {sin(angle *  (M_PI/180)),  cos(angle * (M_PI/180)), 0.0},
        {0.0, 0.0, 1.0}
    };

    for (size_t i = 0; i < points_count; i++){
        int x1, x2, x3;
        x1 = rotate_matrix_z[0][0] * array_points[i][0] +
             rotate_matrix_z[0][1] * array_points[i][1] +
             rotate_matrix_z[0][2] * array_points[i][2];
        x2 = rotate_matrix_z[1][0] * array_points[i][0] +
             rotate_matrix_z[1][1] * array_points[i][1] +
             rotate_matrix_z[1][2] * array_points[i][2];
        x3 = rotate_matrix_z[2][0] * array_points[i][0] +
             rotate_matrix_z[2][1] * array_points[i][1] +
             rotate_matrix_z[2][2] * array_points[i][2];
        print(i+1, "-ая точка (", array_points[i][0], "; ", array_points[i][1], ";", array_points[i][2],
              ") имеет новые координаты (", x1, "; ", x2,";", x3, ")\n");
    }
}
