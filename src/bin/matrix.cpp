#include "matrix.h"

#include "custom_structs.h"
#include <iostream>
#include <vector>
#include <cstddef>

Matrix::Matrix(size_t m, size_t n){
    this->m = m; // строк
    this->n = n; // столбцов
    std::vector<long double> v(n, 0);
    for(size_t i = 0; i < m; ++i){
        this->a.push_back(v);
    }
}

Matrix::Matrix(const Matrix& other) : m(other.m), n(other.n), a(other.a) {}

Matrix::Matrix(Vec3f v){
    this->m = 3;
    this->n = 1;
    std::vector<long double> va(1, v.x);
    this->a.push_back(va);
    std::vector<long double> vb(1, v.y);
    this->a.push_back(vb);
    std::vector<long double> vc(1, v.z);
    this->a.push_back(vc);
}

/*Matrix::Matrix(std::vector<std::vector<long double> > mat){
    this->m = mat.size();
    this->n = mat[0].size();
    for (size_t i = 0; i < m; ++i)
      for(size_t j = 0; j < n; ++j)
        this->a[i][j] = m[i][j];
}*/

Matrix::Matrix(Vertex3_normals vertices_normals){ // конструктор запишет в матрицу векторы нормали как столбцы в однородных координатах(дополнит векторы нормали нулями)

    this->m = 4;
    this->n = 3;

    std::vector<long double> v(n, 0);
    for(size_t i = 0; i < m; ++i){
        this->a.push_back(v);
    }
    
    a[0][0] = vertices_normals.a.x;
    a[0][1] = vertices_normals.b.x;
    a[0][2] = vertices_normals.c.x;
    
    a[1][0] = vertices_normals.a.y;
    a[1][1] = vertices_normals.b.y;
    a[1][2] = vertices_normals.c.y;

    a[2][0] = vertices_normals.a.z;
    a[2][1] = vertices_normals.b.z;
    a[2][2] = vertices_normals.c.z;

    a[3][0] = 0.0L;
    a[3][1] = 0.0L;
    a[3][2] = 0.0L;
}

Matrix Matrix::identity(size_t n){
    Matrix m(n, n);
    for(size_t i = 0; i < n; ++i){
        m[i][i] = 1;
    }
    return m;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix){
    for(size_t i = 0; i < matrix.a.size(); ++i){
        for(size_t j = 0; j < matrix.a[i].size(); ++j){
            os << matrix.a[i][j] <<" ";
        }
        os << "\n";
    }
    return os;
}

long double& Matrix::Row::operator[](size_t col){
    return this->row[col];
}

Matrix::Row Matrix::operator[](size_t row){
    return Row(a[row]);
}

Matrix Matrix::operator*(const Matrix &other) const{
    if(n != other.m){
        std::cout<<"not valid size of matrix: "<<n<<", "<<other.m<<"\n";
        return Matrix(0, 0);
    }
    Matrix result(m, other.n);
    for(size_t i = 0; i < m; ++i){
        for(size_t j = 0; j < other.n; ++j){
            long double s = 0;
            for(size_t u = 0; u < n; ++u){
                s += a[i][u] * other.a[u][j];
            }
            result[i][j] = s;
        }
    }
    return result;
}

Matrix& Matrix::sanitize(){
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (std::isnan(a[i][j])) {
                    a[i][j] = (i == j) ? 1.0L : 0.0L;
                }
            }
        }
        return *this;
}

Matrix Matrix::get_transpose(){
        Matrix t_mat(n, m);
        for (size_t j = 0; j < n; ++j) {
            for (size_t i = 0; i < m; ++i) {
                t_mat[j][i] = a[i][j];
            }
        }
        return t_mat;
}

Matrix Matrix::get_inverse() {
        if (m != n) {
            throw std::runtime_error("Matrix must be square to compute inverse");
        }

        size_t n = m;
        Matrix inverse(n, n);
        Matrix temp(*this); // Копия исходной матрицы

        // Создаем единичную матрицу
        for (size_t i = 0; i < n; ++i) {
            inverse.a[i][i] = 1.0;
        }

        // Прямой ход метода Гаусса
        for (size_t k = 0; k < n; ++k) {
            // Поиск ведущего элемента
            size_t max_row = k;
            for (size_t i = k + 1; i < n; ++i) {
                if (std::abs(temp.a[i][k]) > std::abs(temp.a[max_row][k])) {
                    max_row = i;
                }
            }

            // Перестановка строк
            if (max_row != k) {
                std::swap(temp.a[k], temp.a[max_row]);
                std::swap(inverse.a[k], inverse.a[max_row]);
            }

            // Проверка на вырожденность
            if (std::abs(temp.a[k][k]) < 1e-12) {
                throw std::runtime_error("Matrix is singular (non-invertible)");
            }

            // Нормализация строки
            long double div = temp.a[k][k];
            for (size_t j = 0; j < n; ++j) {
                temp.a[k][j] /= div;
                inverse.a[k][j] /= div;
            }

            // Исключение
            for (size_t i = 0; i < n; ++i) {
                if (i != k && std::abs(temp.a[i][k]) > 1e-12) {
                    long double factor = temp.a[i][k];
                    for (size_t j = 0; j < n; ++j) {
                        temp.a[i][j] -= temp.a[k][j] * factor;
                        inverse.a[i][j] -= inverse.a[k][j] * factor;
                    }
                }
            }
        }

        return inverse;
}
