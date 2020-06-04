#ifndef RENDERER_H
#define RENDERER_H

#include <Generator.h>
#include <Triangulation.h>
#include <SDL2/SDL.h>

class Renderer
{
    public:
        Renderer();

        void drawStart();
        void drawEnd();

        void Draw(Polygon_2 polygon);
        void Draw(vector<Triangle> triangles);
        void Draw(vector<Node> dualTree);

    protected:

    private:
        SDL_Event event;
        SDL_Window * window;
        SDL_Renderer * renderer;
};

#endif // RENDERER_H
