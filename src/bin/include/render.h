#pragma once

#include <vector>
#include <utility>
#include "../../lib/SDL/include/SDL.h"
#include "custom_structs.h"

class Render{
    public:

    SDL_Renderer* render;

    Render();

    Render(SDL_Renderer* render);

    void draw_line(int x1, int y1, int x2, int y2);

    void triangle(Vec3i a, Vec3i b, Vec3i c, Color color, std::vector<long double> &zbuffer);
};
