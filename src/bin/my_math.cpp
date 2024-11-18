#include "my_math.h"
#include "custom_structs.h"

Vec4f plane_equation_solve(Vec3i p1, Vec3i p2, Vec3i p3){     // вычисление координат плоскости заданной тремя точками
    long double A = (p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y);
    long double B = -((p2.x - p1.x) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.x - p1.x));
    long double C = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    long double D = -(A * p1.x + B * p1.y + C * p1.z);
    Vec4f ans = {A, B, C, D};
    return ans;
}
