#include <bits/stdc++.h>
#include <SDL2/SDL.h>

using namespace std;

struct Vec3i{
    int x;
    int y;
    int z;
};

struct Vec2i{
    int x;
    int y;
};

struct Vec4f{
    long double a;
    long double b;
    long double c;
    long double d;
};

struct Vertex{
    long double x;
    long double y;
    long double z;
};

struct Color{
    Uint8 r;
    Uint8 g;
    Uint8 b;
};

const int width = 800;
const int height = 800;
const int depth = 255;

void draw_line(SDL_Renderer* render, int x1, int y1, int x2, int y2) {      // отрисовка отрезка алгоритмом брезенхема
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    bool steep = false;
    if (abs(x1 - x2) < abs(y1 - y2)) {
        swap(x1, y1);
        swap(x2, y2);
        steep = true;
    }
    if (x1 > x2) {
        swap(x1, x2);
        swap(y1, y2);
    }
    int dx = x2 - x1;
    int dy = y2 - y1;
    int derror = abs(dy)*2;
    int error = 0;
    int y = y1;
    for (int x = x1; x <= x2; ++x) {
        if (steep) {
            SDL_RenderDrawPoint(render, y, x);
        } else {
            SDL_RenderDrawPoint(render, x, y);
        }
        error += derror;
        if (error > dx) {
            if(y2 > y1) {
                y += 1;
            } else {
                y += -1;
            }
            error -= dx*2;
        }
    }
}

Vec4f plane_equation_solve(Vec3i p1, Vec3i p2, Vec3i p3){     // вычисление координат плоскости заданной тремя точками
    long double A = (p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y);
    long double B = -((p2.x - p1.x) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.x - p1.x));
    long double C = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    long double D = -(A * p1.x + B * p1.y + C * p1.z);
    Vec4f ans = {A, B, C, D};
    return ans;
}

void triangle(SDL_Renderer* render, Vec3i a, Vec3i b, Vec3i c, Color color, vector<long double> &zbuffer) {        // функция отрисовки треугольника
    
    SDL_SetRenderDrawColor(render, color.r, color.g, color.b, 255);

    if (a.y > b.y) swap(a, b);
    if (a.y > c.y) swap(a, c);
    if (b.y > c.y) swap(b, c);
    
    int x1, x2;

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
            swap(x1, x2);

        for(int x = x1; x <= x2; ++x){
            if(x <= width && y <= height && x >=0 && y >= 0){
                long double z = (-koef_plane.a*x - koef_plane.b*y - koef_plane.d) / (long double)koef_plane.c;
                if(zbuffer[x + y * width] < z){
                    zbuffer[x + y * width] = z;
                    SDL_RenderDrawPoint(render, x, y);
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
            swap(x1, x2);

        for(int x = x1; x <= x2; ++x){
            if(x <= width && y <= height && x >=0 && y >= 0){
                long double z = (-koef_plane.a*x - koef_plane.b*y - koef_plane.d) / (long double)koef_plane.c;
                if(zbuffer[x + y * width] < z){     // если z-координата меньше только тогда отрисовываем треугольник, обновляем zbuffer
                    zbuffer[x + y * width] = z;
                    SDL_RenderDrawPoint(render, x, y);
                }
            }
        }
    }
}

int main() {

    SDL_Window* window = NULL;
    SDL_Renderer* render = NULL;
    bool quit = false;
    
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("engine 0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);    // инициализируем начальные значения для открытия окна
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    
    
    auto f = freopen("/home/coucco/3d_engine_on_c/src/obj/african_head.obj", "r", stdin);   // открываем файл модельки
    
    string s, t;
    vector<Vertex> vertices;
    vector<Vec3i> triangles;
    long double a, b, c;
    int i1, i2, i3;
    while(cin>>s){
        if(s == "v") {
            cin >> a >> b >> c;
            Vertex vert = {a, b, c};
            vertices.push_back(vert);
        }
        if(s == "f") {
            cin >> i1 >> t >> i2 >> t >> i3 >> t;       // парсер граней и вершин модельки
            --i1;
            --i2;
            --i3;
            Vec3i triangle = {i1, i2, i3};
            triangles.push_back(triangle);
        }
    }

    vector<long double> zbuffer;
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
