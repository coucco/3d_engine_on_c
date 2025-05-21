#pragma once

#include "custom_structs.h"
#include <iostream>
#include <vector>
#include <cstddef>

class Matrix{
    public:

        size_t m, n;
        std::vector<std::vector<long double> > a;

        Matrix(size_t m, size_t n);

        Matrix(Vec3f v);

        Matrix(std::vector<std::vector<long double> > m);

        Matrix(Vertex3_normals vertices_normals);

        static Matrix identity(size_t n);

        Matrix operator*(const Matrix &other) const;

        friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

        class Row{
            public:

                Row(std::vector<long double>& row) : row(row) {}

                long double& operator[](size_t col); 

            private:

                std::vector<long double> &row;
        };

        Row operator[](size_t row);

        Matrix& sanitize();

        Matrix get_transpose();
};
