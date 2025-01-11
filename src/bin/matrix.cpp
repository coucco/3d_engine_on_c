#include "matrix.h"

#include <iostream>
#include <vector>
#include <cstddef>
#include <custom_structs.h>

Matrix::Matrix(size_t m, size_t n){
    this->m = m;
    this->n = n;
    std::vector<long double> v(n, 0);
    for(size_t i = 0; i < m; ++i){
        this->a.push_back(v);
    }
}

Matrix::Matrix(Vec3f v){
    this->m = 3;
    this->n = 1;
    std::vector<long double> va(1, v.a);
    this->a.push_back(va);
    std::vector<long double> vb(1, v.b);
    this->a.push_back(vb);
    std::vector<long double> vc(1, v.c);
    this->a.push_back(vc);
}

Matrix Matrix::identity(size_t n){
    Matrix m(n, n);
    for(size_t i = 1; i <= n; ++i){
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
        std::cout<<"not valid size of matrix \n";
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
