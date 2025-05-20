#include "move.h"

#include "custom_structs.h"
#include "matrix.h"
#include "my_math.h"
#include "constants.h"
#include <iostream>

Matrix lookat(Vec3f eye, Vec3f center, Vec3f up){
    Vec3f z = (eye - center).normalize();
    Vec3f x = cross(up, z).normalize();
    Vec3f y = cross(z, x).normalize();
    Matrix Minv = Matrix::identity(4);
    Matrix Tr   = Matrix::identity(4);
    for(int i = 0; i < 3; ++i){
        Minv[0][i] = x[i];
        Minv[1][i] = y[i];
        Minv[2][i] = z[i];
        Tr[i][3] = -eye[i];
    }
    Matrix ModelView = Minv*Tr;
    ModelView.sanitize();
    return ModelView;
}

Matrix viewport(long double x, long double y) { // to turn [-1, 1] * [-1, 1] -> [hole width] * [hole height] 
    Matrix m = Matrix::identity(4);
    m[0][3] = x+width/2.f;
    m[1][3] = y+height/2.f;
    m[2][3] = depth/2.f;

    m[0][0] = width/2.f;
    m[1][1] = height/2.f;
    m[2][2] = depth/2.f;
    return m;
}
