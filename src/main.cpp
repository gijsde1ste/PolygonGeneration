#include <Grid.h>
#include <Triangulation.h>
#include <Renderer.h>

int main() {
    //Grid grid = Grid(200, 200);
    //Polygon_2 p = grid.CreatePolygon();

    Generator generator;
    Polygon_2 p = generator.GeneratePolygon(20, 0.45, Point_2(0,0));

    Triangulation t;
    t.Triangulate(p);
    t.AssignPostOrder(0);
    t.FormatPostOrder();
    t.Save("test.tpie");

    Renderer renderer;
    renderer.Draw(t.dualTree);

    return 0;

}

