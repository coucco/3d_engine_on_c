#pragma once

#include <utility>
#include <SDL2/SDL.h>

class Render{
    public:

    SDL_Renderer* render;

    Render();

    Render(SDL_Renderer* render);

    void draw_line(int x1, int y1, int x2, int y2);
};
