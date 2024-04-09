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

struct Color{
    Uint8 r;
    Uint8 g;
    Uint8 b;
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

void triangle(SDL_Renderer* render, Vec2i a, Vec2i b, Vec2i c, Color color) {

    SDL_SetRenderDrawColor(render, color.r, color.g, color.b, 255);

    if (a.y > b.y) swap(a, b);
    if (a.y > c.y) swap(a, c);
    if (b.y > c.y) swap(b, c)
    
    int x1, x2;

    for(int y = a.y; y <= b.y; ++y) {
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
            if(x <= width && y <= height && x >=0 && y >= 0)
                SDL_RenderDrawPoint(render, x, y);
        }
    }
    
    for(int y = b.y; y <= c.y; ++y) {
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
            if(x <= width && y <= height && x >=0 && y >= 0)
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

    Vec2i a1 = {20, 20}, b1 = {120, 10}, c1 = {101, 30};
    Color gray = {128, 128, 128};
    triangle(render, a1, b1, c1, gray);
    Vec2i a2 = {120, 120}, b2 = {180, 120}, c2 = {160, 290};
    triangle(render, a2, b2, c2, gray);
    Vec2i a3 = {1000, 20}, b3 = {1000, 120}, c3 = {800, 20};
    triangle(render, a3, b3, c3, gray);

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