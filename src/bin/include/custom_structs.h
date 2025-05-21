#pragma once

#include "../../lib/SDL/include/SDL.h"
#include <cmath>
#include <vector>
#include <stdexcept>

struct Vec3i{
    int x;
    int y;
    int z;

    Vec3i() : x(0), y(0), z(0) {}

    Vec3i(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}

    int operator[](int i){
        if (i == 0) return x;
        if (i == 1) return y;
        if (i == 2) return z;
        throw std::out_of_range("Vec3i index out of range");
    }

    void operator=(Vec3i other){
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
    }
};

struct Vec2i{
    int x;
    int y;
};

class Vec3f{
    public:
        long double a;
        long double b;
        long double c;

        Vec3f(long double a, long double b, long double c) : a(a), b(b), c(c) {}

        Vec3f normalize(){
            long double length = sqrt(a*a + b*b + c*c);
            return Vec3f{
                a/length,  // a
                b/length,   // b
                c/length    // c
            };
        }

        float operator[](int i){
            if (i == 0) return a;
            if (i == 1) return b;
            if (i == 2) return c;
            throw std::out_of_range("Vec3f index out of range");
        }

        Vec3f operator+(Vec3f other){
            return Vec3f{
                a + other.a,
                b + other.b,
                c + other.c
            };
        }

        Vec3f operator-(Vec3f other){
            return Vec3f{
                a - other.a,
                b - other.b,
                c - other.c
            };
        }
};

struct Vec4f{
    long double a;
    long double b;
    long double c;
    long double d;
};

struct Vertex{
    long double x;
    long double y;
    long double z;
};

struct Color{
    Uint8 r;
    Uint8 g;
    Uint8 b;
};

struct Texture_2d_cord{
    long double x;
    long double y;
};

struct Norm_vector{
    long double x;
    long double y;
    long double z;
};

class Vertex3_normals{
    public:

    Norm_vector a;
    Norm_vector b;
    Norm_vector c;

    Vertex3_normals(Norm_vector a, Norm_vector b, Norm_vector c) : a(a), b(b), c(c) {}

    Vertex3_normals(std::vector<std::vector<long double> > mat){ // конструктор для обратного получения нормалей из матрицы
        this->a.x = mat[0][0];
        this->b.x = mat[0][1];
        this->c.x = mat[0][2];

        this->a.y = mat[1][0];
        this->b.y = mat[1][1];
        this->c.y = mat[1][2];

        this->a.z = mat[2][0];
        this->b.z = mat[2][1];
        this->c.z = mat[2][2];
    }
};
