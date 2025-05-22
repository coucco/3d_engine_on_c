#include "my_math.h"

#include "custom_structs.h"
#include "matrix.h"
#include <iostream>

Vec4f plane_equation_solve(Vec3i p1, Vec3i p2, Vec3i p3){     // вычисление координат плоскости заданной тремя точками
    long double A = (p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y);
    long double B = -((p2.x - p1.x) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.x - p1.x));
    long double C = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    long double D = -(A * p1.x + B * p1.y + C * p1.z);
    Vec4f ans = {A, B, C, D};
    return ans;
}

Vec3f baricentric_koefs(Vec3i a, Vec3i b, Vec3i c, Vec3i point){
    long double detT = (b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y);
    long double a_k = ((b.y - c.y) * (point.x - c.x) + (c.x - b.x) * (point.y - c.y)) / detT;
    long double b_k = ((c.y - a.y) * (point.x - c.x) + (a.x - c.x) * (point.y - c.y)) / detT;
    long double c_k = 1.0 - a_k - b_k;
    Vec3f ans = {a_k, b_k, c_k};
    return ans;
}

Vec3f cross(Vec3f a, Vec3f b){
    return Vec3f{
        a.y * b.z - a.z * b.y,  // a
        a.z * b.x - a.x * b.z,   // b
        a.x * b.y - a.y * b.x    // c
    };
}
