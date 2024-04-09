// g++ -o main -O3 src/bin/main.cpp `sdl2-config --cflags --libs`
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

struct Vertex{
    long double x;
    long double y;
    long double z;
};

int width = 1080;
int height = 1080;

void draw_line(SDL_Renderer* render, int x1, int y1, int x2, int y2) {
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

void triangle(SDL_Renderer* render, Vec2i a, Vec2i b, Vec2i c) {
    if (a.y > b.y) swap(a, b);
    if (a.y > c.y) swap(a, c);
    if (b.y > c.y) swap(b, c);

    //a
    //b
    //c

    for(int y = a.y; y <= b.y; ++y) {
        /*a -> b
        a.y = k * a.x + b
        b.y = k * b.x + b

        a.y - b.y = k * (a.x - b.x)
        */

        float k = (a.y - b.y) / (a.x - b.x);
        float b = a.y - a.x * k;

        /*a -> c
        a.y = k1 * a.x + b1
        c.y = k1 * c.x + b1
        */

        float k1 = (a.y - c.y) / (a.x - c.x);
        float b1 = a.y - a.x * k1;

        /*y = kx1 + b
        y = k1x2 + b1

        x1 = (y - b) / k
        x2 = (y - b1) / k1
        */

        float x1 = (y - b) / k;
        float x2 = (y - b1) / k1;
        for(int x = x1; x <= x2; ++x){
            SDL_RenderDrawPoint(render, x, y);
        }
    }
}

int main() {

    SDL_Window* window = NULL;
    SDL_Renderer* render = NULL;
    bool quit = false;
    
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("engine 0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    
    
    /*auto f = freopen("/home/coucco/3d_engine_on_c/src/obj/african_head.obj", "r", stdin);
    
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
    }*/

    /*for (auto k : vertices) {
        cout << k.a << " " << k.b << " " << k.c << endl;    // проверка парсера
    }
    cout << "---------" << endl;
    cout << "triangles" << endl; 
    cout << "---------" << endl;
    for (auto k : triangles) {
        cout << k.x << " " << k.y << " " << k.z << endl;
    }*/

    /*int x0, y0, x1, y1;
    for (int i = 0; i < size(triangles); ++i) {
        x0 = (vertices[triangles[i].x].x + 1.) * width/2.;
        y0 = height - (vertices[triangles[i].x].y + 1.) * height/2.;
        x1 = (vertices[triangles[i].y].x + 1.) * width/2.;
        y1 = height - (vertices[triangles[i].y].y + 1.) * height/2.;
        draw_line(render, x0, y0, x1, y1);
        x1 = (vertices[triangles[i].z].x + 1.) * width/2.;         // отрисовка проволочной сетки
        y1 = height - (vertices[triangles[i].z].y + 1.) * height/2.;
        draw_line(render, x0, y0, x1, y1);
        x0 = (vertices[triangles[i].y].x + 1.) * width/2.;
        y0 = height - (vertices[triangles[i].y].y + 1.) * height/2.;
        draw_line(render, x0, y0, x1, y1);
    }*/

    Vec2i a1 = {20, 20}, b1 = {100, 100}, c1 = {30, 80};
    triangle(render, a1, b1, c1);

    SDL_RenderPresent(render);
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            }
        }
    }
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}