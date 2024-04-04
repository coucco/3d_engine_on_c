// g++ -o main -O3 src/bin/main.cpp `sdl2-config --cflags --libs`
#include <bits/stdc++.h>
#include <SDL2/SDL.h>

using namespace std;

struct Vec3i{
    int x;
    int y;
    int z;
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

/*void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color) {
    if (t0.y>t1.y) std::swap(t0, t1);
    if (t0.y>t2.y) std::swap(t0, t2);
    if (t1.y>t2.y) std::swap(t1, t2);

    int total_height = t2.y-t0.y;
    for (int y=t0.y; y<=t1.y; y++) {
        int segment_height = t1.y-t0.y+1;
        float alpha = (float)(y-t0.y)/total_height;
        float beta  = (float)(y-t0.y)/segment_height;
        Vec2i A = t0 + (t2-t0)*alpha;
        Vec2i B = t0 + (t1-t0)*beta;
        image.set(A.x, y, red);
        image.set(B.x, y, green);
    }
}*/

int main() {

    SDL_Window* window = NULL;
    SDL_Renderer* render = NULL;
    bool quit = false;
    
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("engine 0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    
    
    auto f = freopen("/home/coucco/3d_engine_on_c/src/obj/african_head.obj", "r", stdin);
    
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

    /*for (auto k : vertices) {
        cout << k.a << " " << k.b << " " << k.c << endl;    // проверка парсера
    }
    cout << "---------" << endl;
    cout << "triangles" << endl; 
    cout << "---------" << endl;
    for (auto k : triangles) {
        cout << k.x << " " << k.y << " " << k.z << endl;
    }*/

    int x0, y0, x1, y1;
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
    }

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