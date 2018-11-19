#include "ffhelpers.h" /// для упрощения ввода-вывода

using namespace std;
using namespace ffomsu;

class SquareMatrix
{
public:
    SquareMatrix(size_t N);
    ~SquareMatrix();

    double get(size_t i, size_t j);
    void   set(size_t i, size_t j, double value);
    double det();
    size_t size();

private:
    double **_matr;
    size_t _size;

    double determinant(double **matr, size_t matr_size);
};

void print_sq_matrix(SquareMatrix& matrix)
{
    const size_t sz = matrix.size();
    for (size_t i = 0; i < sz; i++) {
        for (size_t j = 0; j < sz; j++) {
            print(setw(5), matrix.get(i, j), " ");
        }
        print("\n");
    }
    print("\n");
}

int main()
{
    /**
        Вычисление определителя следующей матрицы 3х3:
            / 2  1  1 \
            | 1  3  3 |
            \ 4  5 -3 /
    */
    SquareMatrix matr{3};
    matr.set(0, 0, 2); matr.set(0, 1, 1); matr.set(0, 2, 1);
    matr.set(1, 0, 1); matr.set(1, 1, 3); matr.set(1, 2, 3);
    matr.set(2, 0, 4); matr.set(2, 1, 5); matr.set(2, 2, -3);
    print("det(matr) = ", matr.det(), endl);

    SquareMatrix matr5x5{5};

    for (size_t i = 0; i < matr5x5.size(); i++) {
      for (size_t j = 0; j < matr5x5.size(); j++) {
        matr5x5.set(i, j, rand_a_b_incl(2.5, 7.5));
      }
    }

    print_sq_matrix(matr5x5);

    print("Размер матрицы: ", matr5x5.size(), "\n");
    print("2-ой элемент 3-ой строки: ", matr5x5.get(2, 1), '\n');
    print("Определитель: ", matr5x5.det(), "\n");
}

SquareMatrix::SquareMatrix(size_t N)
{
    _size = N;
    _matr = new double*[_size];
    for (size_t i = 0; i < _size; i++) {
        _matr[i] = new double[_size];
    }
}

SquareMatrix::~SquareMatrix()
{
    for (size_t i = 0; i < _size; i++) {
        delete[] _matr[i] = new double[_size];
    }
    delete[] _matr;
}

double SquareMatrix::get(size_t i, size_t j)
{
    return _matr[i][j];
}

void SquareMatrix::set(size_t i, size_t j,
                       double value)
{
    _matr[i][j] = value;
}

size_t SquareMatrix::size()
{
    return _size;
}

double SquareMatrix::det()
{
    return determinant(_matr, _size);
}

double SquareMatrix::determinant(double **matr, size_t matr_size)
{
    if (matr_size == 2) {
        return matr[0][0] * matr[1][1] - matr[0][1] * matr[1][0];
    }

    double result = 0.0;
    double **help_matr = new double*[matr_size-1];
    for (size_t i = 0; i < matr_size-1; i++) {
        help_matr[i] = new double[matr_size-1];
    }

    for (size_t j = 0; j < matr_size; j++) {
        int sign_scale = (j % 2 == 0) ? 1 : -1;

        for (size_t i = 1; i < matr_size; i++) {
            for (size_t k = 0, ind = 0; k < matr_size; k++) {
                if (k == j) {
                    continue;
                }

                help_matr[i-1][ind] = matr[i][k];
                ind++;
            }
        }

        result += sign_scale * matr[0][j] * determinant(help_matr, matr_size - 1);
    }

    for (size_t i = 0; i < matr_size-1; i++) {
        delete[] help_matr[i];
    }
    delete[] help_matr;

    return result;
}
