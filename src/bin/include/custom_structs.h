#pragma once

#include "../../lib/SDL/include/SDL.h"

struct Vec3i{
    int x;
    int y;
    int z;
};

struct Vec2i{
    int x;
    int y;
};

struct Vec3f{
    long double a;
    long double b;
    long double c;
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

struct Vertex3_normals{
    Norm_vector a;
    Norm_vector b;
    Norm_vector c;
};
