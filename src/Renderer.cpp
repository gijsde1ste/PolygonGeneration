#include "Renderer.h"

Renderer::Renderer()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 960, 0);
    renderer = SDL_CreateRenderer(window, -1 , 0);
}

void Renderer::Draw(Polygon_2 polygon)
{
    drawStart();

    double prevX = CGAL::to_double((*polygon.vertices_begin()).x());
    double prevY = CGAL::to_double((*polygon.vertices_begin()).y());
    for (auto vi = polygon.vertices_begin(); vi != polygon.vertices_end(); ++vi)
    {
        double x = CGAL::to_double((*vi).x());
        double y = CGAL::to_double((*vi).y());

        SDL_RenderDrawLine(renderer, prevX * 200, prevY * 200, x * 200, y * 200);

        prevX = x;
        prevY = y;
    }

    SDL_RenderDrawLine(renderer, prevX * 200, prevY * 200, CGAL::to_double((*polygon.vertices_begin()).x()) * 200, CGAL::to_double((*polygon.vertices_begin()).y())* 200);

    drawEnd();
}

void Renderer::Draw(vector<Triangle> triangles)
{
    drawStart();

    Triangle t;
    for (auto i = triangles.begin(); i != triangles.end(); i++){
        t = *i;
        SDL_RenderDrawLine(renderer, t[0].x() * 200, t[0].y() * 200, t[1].x() * 200, t[1].y() * 200);
        SDL_RenderDrawLine(renderer, t[1].x() * 200, t[1].y() * 200, t[2].x() * 200, t[2].y() * 200);
        SDL_RenderDrawLine(renderer, t[2].x() * 200, t[2].y() * 200, t[0].x() * 200, t[0].y() * 200);
    }

    drawEnd();
}

void Renderer::Draw(vector<Node> dualTree)
{
    drawStart();

    Point_2 p1, p2, p3;
    for (auto i = dualTree.begin(); i != dualTree.end(); i++){
        p1 = i->points[0];
        p2 = i->points[1];
        p3 = i->points[2];

        SDL_RenderDrawLine(renderer, p1.x() * 200, p1.y() * 200, p2.x() * 200, p2.y() * 200);
        SDL_RenderDrawLine(renderer, p2.x() * 200, p2.y() * 200, p3.x() * 200, p3.y() * 200);
        SDL_RenderDrawLine(renderer, p3.x() * 200, p3.y() * 200, p1.x() * 200, p1.y() * 200);
    }

    drawEnd();
}

void Renderer::drawStart(){
    // Clear screen white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw with black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Renderer::drawEnd(){
    SDL_RenderPresent(renderer);

    while( true ){
        SDL_Delay(10);
        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT){
            break;
        }
    };

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
