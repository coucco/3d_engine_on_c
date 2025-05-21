#include "model.h"

#include <iostream>
#include <vector>
#include <string>
#include "../lib/SDL/include/SDL.h"
#include "custom_structs.h"
#include "constants.h"
#include "render.h"
#include "matrix.h"
#include "move.h"
#include <cstdio>
#include <climits>
#include <cmath>

Model::Model(const char* model_path, Render render_main){

    this->render = render_main;

    this->model_file = freopen(model_path, "r", stdin); // путь по которому лежит моделька в формате .obj
    // путь может быть абсолютным либо относительно папки с проектом с указанием в начале префикса ../

    std::string s, t;
    char c;
    long double x, y, z;
    int v1, v2, v3, vt1 = 0, vt2 = 0, vt3 = 0, vn1 = 0, vn2 = 0, vn3 = 0;
    while(std::cin>>s){
        if(s == "v") {
            std::cin >> x >> y >> z;
            if(x < this->min_vx){
                this->min_vx = x;
            }
            if(y < this->min_vy){
                this->min_vy = y;
            }
            if(z < this->min_vz){
                this->min_vz = z;
            }
            if(x > this->max_vx){
                this->max_vx = x;
            }
            if(y > this->max_vy){
                this->max_vy = y;
            }
            if(z > this->max_vz){
                this->max_vz = z;
            }
            Vertex vert = {x, y, z};
            this->vertices.push_back(vert);
        }
        if(s == "vt") {
            std::cin >> x >> y;
            Texture_2d_cord textcord = {x, y}; // z = 0.0
            this->texture_2d_cords.push_back(textcord);
        }
        if(s == "vn") {
            std::cin >> x >> y >> z;
            Norm_vector normal = {x, y, z};
            this->vertex_normals.push_back(normal);
        }
        if(s == "f") {
            int ind1 = -1, ind2 = -1;
            std::cin >> t;                                       // парсер граней и вершин модельки
            for(size_t i = 0; i < size(t); ++i){
                if(t[i] == '/'){
                    if(ind1 == -1)
                        ind1 = i;
                    else
                        ind2 = i;
                }
            }
            v1 = std::stoi((t.substr(0, ind1)));
            if(ind1 + 1 != ind2)
                vt1 = std::stoi((t.substr(ind1+1, ind2-ind1-1)));
            else
                vt1 = -1;
            vn1 = std::stoi((t.substr(ind2+1, size(t)-ind2)));

            ind1 = -1;
            ind2 = -1;
            std::cin >> t;
            for(size_t i = 0; i < size(t); ++i){
                if(t[i] == '/'){
                    if(ind1 == -1)
                        ind1 = i;
                    else
                        ind2 = i;
                }
            }
            v2 = std::stoi((t.substr(0, ind1)));
            if(ind1 + 1 != ind2)
                vt2 = std::stoi((t.substr(ind1+1, ind2-ind1-1)));
            else
                vt2 = -1;
            vn2 = std::stoi((t.substr(ind2+1, size(t)-ind2)));

            ind1 = -1;
            ind2 = -1;
            std::cin >> t;
            for(size_t i = 0; i < size(t); ++i){
                if(t[i] == '/'){
                    if(ind1 == -1)
                        ind1 = i;
                    else
                        ind2 = i;
                }
            }
            v3 = std::stoi((t.substr(0, ind1)));
            if(ind1 + 1 != ind2)
                vt2 = std::stoi((t.substr(ind1+1, ind2-ind1-1)));
            else
                vt2 = -1;
            vn3 = std::stoi((t.substr(ind2+1, size(t)-ind2)));

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

    long double model_length = std::max(max_vx - min_vx, std::max(max_vy - min_vy, max_vz - min_vz));

    for(size_t i = 0; i < size(this->vertices); ++i){
        this->vertices[i].x = this->vertices[i].x / model_length * 2;
        this->vertices[i].y = this->vertices[i].y / model_length * 2;
        this->vertices[i].z = this->vertices[i].z / model_length * 2;
    }

    for(size_t i = 0; i < width*height; ++i){
        this->zbuffer.push_back(-INT_MAX / 100.);       // инициализация zbuffer значениями -inf 
    }
}

void Model::camera_movement_polygon_smooth(Vec3f eye, Vec3f center, Vec3f up){
    for(size_t i = 0; i < width*height; ++i){
        this->zbuffer[i] = -INT_MAX;       // инициализация zbuffer значениями -inf 
    }    

    Matrix v_m(4, 1);
    Matrix M = viewport(0, 0) * lookat(eye, center, up); // делаем цепочку преобразований
    Vec3i screen_cords[3];

    for(size_t i = 0; i < size(triangles); ++i){      // перебираем треугольники модельки в цикле

        for(int j = 0; j < 3; ++j){
            v_m[0][0] = vertices[this->triangles[i][j]].x;
            v_m[1][0] = vertices[this->triangles[i][j]].y;
            v_m[2][0] = vertices[this->triangles[i][j]].z;
            v_m[3][0] = 1;
            Matrix screen_cords_m = M * v_m;  // вычисляем координаты вершин в репере камеры
            screen_cords[j] = Vec3i((int)screen_cords_m[0][0], height - (int)screen_cords_m[1][0], (int)screen_cords_m[2][0]);
        }

        Vec3f light = {0.15, 0.2, 0.65};
        light = light.normalize();

        Vertex3_normals vertices_normals = {vertex_normals[normal_triangles[i].x], vertex_normals[normal_triangles[i].y], vertex_normals[normal_triangles[i].z]};
        
        // M * normal_matrix - преобразовываем нормали
        Matrix normal_matrix(vertices_normals);
        Matrix new_vertices_matrix = M * normal_matrix;
        vertices_normals = Vertex3_normals(new_vertices_matrix.a);

        this->render.triangle_smooth(screen_cords[0], screen_cords[1], screen_cords[2], zbuffer, vertices_normals, light);
    }
}
