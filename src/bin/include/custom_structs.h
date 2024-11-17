#pragma once

#include <SDL2/SDL.h>

struct Vec3i{
    int x;
    int y;
    int z;
};

struct Vec2i{
    int x;
    int y;
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
