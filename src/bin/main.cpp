#include "../lib/SDL/include/SDL.h"
#include "constants.h"
#include "custom_structs.h"
#include "matrix.h"
#include "model.h"
#include "my_math.h"
#include "render.h"
#include <cstring>
#include <iostream>

int main(int argc, char *argv[]) {

  SDL_Window *window = NULL;
  SDL_Renderer *render = NULL;

  SDL_Init(SDL_INIT_EVERYTHING);
  window = SDL_CreateWindow("engine 0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0); // инициализируем начальные значения для открытия окна
  render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  SDL_SetRenderDrawColor(render, 255, 255, 255, 255);

  Render main_render(render);

  std::string model_name = argv[1];
  std::string model_path = "../src/obj/" + model_name + ".obj";
  const char *const_char_model_path = model_path.c_str();

  Model model(const_char_model_path, main_render);

  if (strcmp(argv[2], "provolka") == 0) {
    model.provolka();
  }

  if (strcmp(argv[2], "polygon") == 0) {
    model.polygon();
  }

  if (strcmp(argv[2], "zbuffer_check") == 0) {
    model.polygon();
    model.zbuffer_check();
  }

  if (strcmp(argv[2], "polygon_smooth") == 0) {
    model.polygon_smooth();
  }

  SDL_RenderPresent(render);
  bool quit = false;
  while (!quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) { // бесконечный цикл чтобы поддерживать окно открытым
        quit = true;
        break;
      }
    }
  }

  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window); //  удаляем все объекты, заканчиваем работу программы
  SDL_Quit();

  return 0;
}
