#pragma once

#include <iostream>
#include <vector>
#include <cstdio>
#include "../../lib/SDL/include/SDL.h"
#include "custom_structs.h"
#include "constants.h"
#include "render.h"

class Model{
    public:

    FILE* model_file;
    Render render;
    std::vector<Vertex> vertices;
    std::vector<Vec3i> triangles;
    std::vector<long double> zbuffer;

    Model(const char* model_path, Render render_main);

    void provolka();
};
