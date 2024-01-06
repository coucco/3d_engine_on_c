//gcc -o main src/bin/main.c `sdl2-config --cflags --libs`
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;
bool quit = false;

struct Point{
    int x;
    int y;
};

void init_window() {

    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("minecraft 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderClear(render);
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
}

void exit_window() {
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void draw_line(SDL_Renderer* render, struct Point* p1, struct Point* p2) {
    //brezenheim_impl_here
}

void loop_window() {
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            } else {
                //draw_line();
            }
        }
    }
}

int main() {
    
    init_window();

    loop_window();

    exit_window();

    return 0;
}