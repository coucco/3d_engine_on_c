#include <iostream>
#include <cstring>
#include "../lib/SDL/include/SDL.h"
#include "constants.h"
#include "custom_structs.h"
#include "my_math.h"
#include "model.h"
#include "render.h"

int main(int argc, char* argv[]){

    SDL_Window* window = NULL;
    SDL_Renderer* render = NULL;
    bool quit = false;
    
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("engine 0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);    // инициализируем начальные значения для открытия окна
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    
    Render main_render(render);

    Model african_head("../src/obj/african_head.obj", main_render);

    if(strcmp(argv[1], "provolka") == 0){
        african_head.provolka();
    }

    if(strcmp(argv[1], "polygon") == 0){
        african_head.polygon();
    }

    if(strcmp(argv[1], "zbuffer_check") == 0){
        african_head.polygon();
        african_head.zbuffer_check();
    }

    if(strcmp(argv[1], "polygon_smooth") == 0){
        african_head.polygon_smooth();
    }

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
