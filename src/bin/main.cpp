#include <iostream>
#include "../lib/SDL/include/SDL.h"
#include "constants.h"
#include "custom_structs.h"
#include "math.h"
#include "model.h"
#include "render.h"

int main() {

    SDL_Window* window = NULL;
    SDL_Renderer* render = NULL;
    bool quit = false;
    
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("engine 0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);    // инициализируем начальные значения для открытия окна
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    
    Render main_render(render);

    Model african_head("../src/obj/african_head.obj", main_render);

    african_head.provolka();

    /*african_head.zbuffer();
    african_head.render();*/

    /*
    std::vector<long double> zbuffer;
    for(int i = 0; i < width*height; ++i){
        zbuffer.push_back(-INT_MAX / 100.);       // инициализация zbuffer значениями -inf 
    }

    int x0, y0, z0, x1, y1, z1, x2, y2, z2;
    for (int i = 0; i < size(triangles); ++i) {      // перебираем треугольники модельки в цикле

        x0 = (vertices[triangles[i].x].x + 1.) * width/2.;
        y0 = height - (vertices[triangles[i].x].y + 1.) * height/2.;
        z0 = (vertices[triangles[i].x].z + 1.) * depth/2.;

        x1 = (vertices[triangles[i].y].x + 1.) * width/2.;
        y1 = height - (vertices[triangles[i].y].y + 1.) * height/2.;      // вычисляем координаты
        z1 = (vertices[triangles[i].y].z + 1.) * depth/2.;

        x2 = (vertices[triangles[i].z].x + 1.) * width/2.;
        y2 = height - (vertices[triangles[i].z].y + 1.) * height/2.;
        z2 = (vertices[triangles[i].z].z + 1.) * depth/2.;

        Vec3i v1 = {x0, y0, z0}, v2 = {x1, y1, z1}, v3 = {x2, y2, z2};

        long double x0_world = vertices[triangles[i].x].x;
        long double y0_world = vertices[triangles[i].x].y;
        long double z0_world = vertices[triangles[i].x].z;

        long double x1_world = vertices[triangles[i].y].x;
        long double y1_world = vertices[triangles[i].y].y;
        long double z1_world = vertices[triangles[i].y].z;

        long double x2_world = vertices[triangles[i].z].x;
        long double y2_world = vertices[triangles[i].z].y;
        long double z2_world = vertices[triangles[i].z].z;

        long double x0_delta = x2_world - x0_world;
        long double x1_delta = x1_world - x0_world;

        long double y0_delta = y2_world - y0_world;
        long double y1_delta = y1_world - y0_world;

        long double z0_delta = z2_world - z0_world;
        long double z1_delta = z1_world - z0_world;

        long double nx = y0_delta * z1_delta - y1_delta * z0_delta;
        long double ny = z0_delta * x1_delta - x0_delta * z1_delta;   // считаем нормали
        long double nz = x0_delta * y1_delta - x1_delta * y0_delta;

        long double norm = sqrt(nx * nx + ny * ny + nz * nz);

        nx /= norm;
        ny /= norm;
        nz /= norm;

        long double l1 = 0.;
        long double l2 = 0.;            // задаем источники освещения
        long double l3 = -1.;

        long double intensity = l1 * nx + l2 * ny + l3 * nz;
        if(intensity > 0) {
            Uint8 r = intensity * 255 * 0.7, g = intensity * 255 * 0.7, b = intensity * 255 * 0.7;
            Color color = {r, g, b};
            triangle(render, v1, v2, v3, color, zbuffer);       // передаем все что посчитали в функцию отрисовки треугольников
        }
    }
    */

    SDL_RenderPresent(render);
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {           // бесконечный цикл чтобы поддерживать окно открытым
                quit = true;
                break;
            }
        }
    }

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);          //  удаляем все объекты, заканчиваем работу программы
    SDL_Quit();
    
    return 0;
}
