#include "model.h"

#include <iostream>
#include <vector>
#include <string>
#include "../lib/SDL/include/SDL.h"
#include "custom_structs.h"
#include "constants.h"
#include "render.h"
#include <cstdio>
#include <climits>
#include <cmath>

Model::Model(const char* model_path, Render render_main){

    this->render = render_main;

    this->model_file = freopen(model_path, "r", stdin); // путь по которому лежит моделька в формате .obj
    // путь может быть абсолютным либо относительно папки с проектом с указанием в начале префикса ../

    std::string s;
    char c;
    long double x, y, z;
    int v1, v2, v3, vt1, vt2, vt3, vn1, vn2, vn3;
    while(std::cin>>s){
        if(s == "v") {
            std::cin >> x >> y >> z;
            Vertex vert = {x, y, z};
            this->vertices.push_back(vert);
        }
        if(s == "vt") {
            std::cin >> x >> y >> z;
            Texture_2d_cord textcord = {x, y}; // z = 0.0
            this->texture_2d_cords.push_back(textcord);
        }
        if(s == "vn") {
            std::cin >> x >> y >> z;
            Norm_vector normal = {x, y, z};
            this->vertex_normals.push_back(normal);
        }
        if(s == "f") {
            std::cin >> v1 >> c >> vt1 >> c >> vn1 >> v2 >> c >> vt2 >> c >> vn2 >> v3 >> c >> vt3 >> c >> vn3;   // парсер граней и вершин модельки
            --v1;
            --v2;
            --v3;
            Vec3i triangle = {v1, v2, v3};
            this->triangles.push_back(triangle);
            --vt1;
            --vt2;
            --vt3;
            Vec3i triangle_textures = {vt1, vt2, vt3};
            this->texture_triangles.push_back(triangle_textures);
            --vn1;
            --vn2;
            --vn3;
            Vec3i triangle_normals = {vn1, vn2, vn3};
            this->normal_triangles.push_back(triangle_normals);
        }
    }

    for(int i = 0; i < width*height; ++i){
        this->zbuffer.push_back(-INT_MAX / 100.);       // инициализация zbuffer значениями -inf 
    }
}

void Model::provolka(){
    int x0, y0, x1, y1;
    for (int i = 0; i < std::size(this->triangles); ++i) {
        x0 = (this->vertices[this->triangles[i].x].x + 1.) * width/2.;
        y0 = height - (this->vertices[this->triangles[i].x].y + 1.) * height/2.;
        x1 = (this->vertices[this->triangles[i].y].x + 1.) * width/2.;
        y1 = height - (this->vertices[this->triangles[i].y].y + 1.) * height/2.;
        this->render.draw_line(x0, y0, x1, y1);
        x1 = (this->vertices[this->triangles[i].z].x + 1.) * width/2.;                 // отрисовка проволочной сетки
        y1 = height - (this->vertices[this->triangles[i].z].y + 1.) * height/2.;
        this->render.draw_line(x0, y0, x1, y1);
        x0 = (this->vertices[this->triangles[i].y].x + 1.) * width/2.;
        y0 = height - (this->vertices[this->triangles[i].y].y + 1.) * height/2.;
        this->render.draw_line(x0, y0, x1, y1);
    }
}

void Model::polygon(){
    for(int i = 0; i < width*height; ++i){
        this->zbuffer[i] = -INT_MAX / 100.;       // инициализация zbuffer значениями -inf 
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
            Uint8 r = intensity * 255, g = intensity * 255, b = intensity * 255;
            Color color = {r, g, b};
            this->render.triangle(v1, v2, v3, color, zbuffer);       // передаем все что посчитали в функцию отрисовки треугольников
        }
    }
}

void Model::zbuffer_check(){
    for(int i = 0; i < width*height; ++i){
        long double intensity = zbuffer[i] / (long double)depth;  // zbuffer check
        Uint8 r, g, b;
        r = 255 * intensity;
        g = 255 * intensity;
        b = 255 * intensity;
        SDL_SetRenderDrawColor(this->render.render, r, g, b, 255);
        SDL_RenderDrawPoint(this->render.render, i%width, i/width);
    }
}

void Model::polygon_smooth(){
    for(int i = 0; i < width*height; ++i){
        this->zbuffer[i] = -INT_MAX / 100.;       // инициализация zbuffer значениями -inf 
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

        long double l1 = 0.15;
        long double l2 = 0.1;            // задаем источники освещения
        long double l3 = 0.75;

        Vec3f light = {l1, l2, l3};

        Vertex3_normals vertices_normals = {vertex_normals[normal_triangles[i].x], vertex_normals[normal_triangles[i].y], vertex_normals[normal_triangles[i].z]};

        this->render.triangle_smooth(v1, v2, v3, zbuffer, light, vertices_normals);
    }
}
