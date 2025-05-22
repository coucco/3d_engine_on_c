#include "render.h"

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include "../lib/SDL/include/SDL.h"
#include "custom_structs.h"
#include "constants.h"
#include "my_math.h"

Render::Render(SDL_Renderer* render){
    this->render = render;
}

Render::Render(){
    this->render = NULL;
}

void Render::triangle_smooth(Vec3i a, Vec3i b, Vec3i c, std::vector<long double> &zbuffer, Vertex3_normals vertex_normals, Vec3f light){

    if (a.y == b.y && a.y == c.y){
        return;
    }

    if (a.y > b.y){
        std::swap(a, b);
        std::swap(vertex_normals.a, vertex_normals.b);
    }
    if (a.y > c.y){
        std::swap(a, c);
        std::swap(vertex_normals.a, vertex_normals.c);
    }
    if (b.y > c.y){
        std::swap(b, c);
        std::swap(vertex_normals.b, vertex_normals.c);
    }

    int x1, x2;
    long double nx, ny, nz, length, intensity;

    Vec4f koef_plane = plane_equation_solve(a, b, c);

    for(int y = a.y; y <= b.y; ++y) {           // отрисовка первой части треугольника
        if(a.x != b.x){
            long double k = (long double)(a.y - b.y) / (a.x - b.x);
            long double b1 = (long double)a.y - a.x * k;
            if(k < 0.001 && k > -0.001)
                break;
            x1 = floor((y - b1) / k);
        } else {
            x1 = a.x;
        }

        if(a.x != c.x){
            long double k1 = (long double)(a.y - c.y) / (a.x - c.x);
            long double b2 = (long double)a.y - a.x * k1;
            if(k1 < 0.001 && k1 > -0.001)
                break;
            x2 = ceil((y - b2) / k1);
        } else {
            x2 = a.x;
        }

        if(x2 < x1)
            std::swap(x1, x2);

        for(int x = x1; x <= x2; ++x){
            if(x <= width && y <= height && x >=0 && y >= 0){
                long double z = (-koef_plane.a*x - koef_plane.b*y - koef_plane.d) / (long double)koef_plane.c;
                if(zbuffer[x + y * width] < z){
                    zbuffer[x + y * width] = z;
                    Vec3i point = {x, y, static_cast<int>(z)};
                    Vec3f koefs = baricentric_koefs(a, b, c, point);
                    nx = koefs.x * vertex_normals.a.x + koefs.y * vertex_normals.b.x + koefs.z * vertex_normals.c.x;
                    ny = koefs.x * vertex_normals.a.y + koefs.y * vertex_normals.b.y + koefs.z * vertex_normals.c.y;    // интерполируем нормаль внутри треугольника
                    nz = koefs.x * vertex_normals.a.z + koefs.y * vertex_normals.b.z + koefs.z * vertex_normals.c.z;
                    length = sqrt(nx * nx + ny * ny + nz * nz);
                    nx /= length;
                    ny /= length;
                    nz /= length;
                    intensity = light.x * nx + light.y * ny + light.z * nz;
                    if(intensity > 0){
                        Uint8 r = intensity * 255, g = intensity * 255, b = intensity * 255;
                        Color color = {r, g, b};
                        SDL_SetRenderDrawColor(this->render, color.r, color.g, color.b, 255);
                        SDL_RenderDrawPoint(this->render, x, y);
                    }
                }
            }
        }
    }

    for(int y = b.y; y <= c.y; ++y) {           // отрисовка второй части треугольника
        if(b.x != c.x){
            long double k = (long double)(b.y - c.y) / (b.x - c.x);
            long double b1 = (long double)b.y - b.x * k;
            if(k < 0.001 && k > -0.001)
                break;
            x1 = floor((y - b1) / k);
        } else {
            x1 = b.x;
        }

        if(a.x != c.x){
            long double k1 = (long double)(a.y - c.y) / (a.x - c.x);
            long double b2 = (long double)a.y - a.x * k1;
            if(k1 < 0.001 && k1 > -0.001)
                break;
            x2 = ceil((y - b2) / k1);
        } else {
            x2 = a.x;
        }

        if(x2 < x1)
            std::swap(x1, x2);

        for(int x = x1; x <= x2; ++x){
            if(x <= width && y <= height && x >=0 && y >= 0){
                long double z = (-koef_plane.a*x - koef_plane.b*y - koef_plane.d) / (long double)koef_plane.c;
                if(zbuffer[x + y * width] < z){     // если z-координата меньше только тогда отрисовываем треугольник, обновляем zbuffer
                    zbuffer[x + y * width] = z;
                    Vec3i point = {x, y, static_cast<int>(z)};
                    Vec3f koefs = baricentric_koefs(a, b, c, point);
                    nx = koefs.x * vertex_normals.a.x + koefs.y * vertex_normals.b.x + koefs.z * vertex_normals.c.x;
                    ny = koefs.x * vertex_normals.a.y + koefs.y * vertex_normals.b.y + koefs.z * vertex_normals.c.y;    // интерполируем нормаль внутри треугольника
                    nz = koefs.x * vertex_normals.a.z + koefs.y * vertex_normals.b.z + koefs.z * vertex_normals.c.z;
                    length = sqrt(nx * nx + ny * ny + nz * nz);
                    nx /= length;
                    ny /= length;
                    nz /= length;
                    intensity = light.x * nx + light.y * ny + light.z * nz;
                    if(intensity > 0){
                        Uint8 r = intensity * 255, g = intensity * 255, b = intensity * 255;
                        Color color = {r, g, b};
                        SDL_SetRenderDrawColor(this->render, color.r, color.g, color.b, 255);
                        SDL_RenderDrawPoint(this->render, x, y);
                    }
                }
            }
        }
    }
}
