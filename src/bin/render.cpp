#include "render.h"

#include <utility>
#include <SDL2/SDL.h>

Render::Render(SDL_Renderer* render){
    this->render = render;
}

Render::Render(){
    this->render = NULL;
}

void Render::draw_line(int x1, int y1, int x2, int y2) {      // отрисовка отрезка алгоритмом брезенхема
    SDL_SetRenderDrawColor(this->render, 255, 255, 255, 255);
    bool steep = false;
    if (abs(x1 - x2) < abs(y1 - y2)) {
        std::swap(x1, y1);
        std::swap(x2, y2);
        steep = true;
    }
    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    int dx = x2 - x1;
    int dy = y2 - y1;
    int derror = abs(dy)*2;
    int error = 0;
    int y = y1;
    for (int x = x1; x <= x2; ++x) {
        if (steep) {
            SDL_RenderDrawPoint(this->render, y, x);
        } else {
            SDL_RenderDrawPoint(this->render, x, y);
        }
        error += derror;
        if (error > dx) {
            if(y2 > y1) {
                y += 1;
            } else {
                y += -1;
            }
            error -= dx*2;
        }
    }
}
