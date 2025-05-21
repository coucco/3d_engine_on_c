#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "../../lib/SDL/include/SDL.h"
#include "custom_structs.h"
#include "constants.h"
#include "render.h"
#include "matrix.h"
#include "move.h"
#include <cstdio>
#include <climits>
#include <cmath>

class Model{
    public:

    FILE* model_file;
    Render render;
    std::vector<Vertex> vertices;
    std::vector<Texture_2d_cord> texture_2d_cords;
    std::vector<Norm_vector> vertex_normals;
    std::vector<Vec3i> triangles;
    std::vector<Vec3i> texture_triangles;
    std::vector<Vec3i> normal_triangles;
    std::vector<long double> zbuffer;
    int min_vx = INT_MAX;
    int min_vy = INT_MAX;
    int min_vz = INT_MAX;
    int max_vx = INT_MIN;
    int max_vy = INT_MIN;
    int max_vz = INT_MIN;

    Model(const char* model_path, Render render_main);

    void provolka();

    void polygon();

    void zbuffer_check();

    void polygon_smooth();

    void camera_movement_provolka(Vec3f eye, Vec3f center, Vec3f up);

    void camera_movement_polygon_smooth(Vec3f eye, Vec3f center, Vec3f up);
};
