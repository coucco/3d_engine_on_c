#include "model.h"

#include <iostream>
#include <vector>
#include <string>
#include "../lib/SDL/include/SDL.h"
#include "custom_structs.h"
#include "constants.h"
#include "render.h"
#include <cstdio>

Model::Model(const char* model_path, Render render_main){

    this->render = render_main;

    this->model_file = freopen(model_path, "r", stdin); // путь по которому лежит моделька в формате .obj
    // путь может быть абсолютным либо относительно папки с проектом с указанием в начале префикса ../

    std::string s, t;
    long double a, b, c;
    int i1, i2, i3;
    while(std::cin>>s){
        if(s == "v") {
            std::cin >> a >> b >> c;
            Vertex vert = {a, b, c};
            this->vertices.push_back(vert);
        }
        if(s == "f") {
            std::cin >> i1 >> t >> i2 >> t >> i3 >> t;       // парсер граней и вершин модельки
            --i1;
            --i2;
            --i3;
            Vec3i triangle = {i1, i2, i3};
            this->triangles.push_back(triangle);
        }
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
