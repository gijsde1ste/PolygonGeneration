#include "Generator.h"
#include <iostream>

Generator::Generator()
{
    //ctor
}

Polygon_2 Generator::GeneratePolygon(int size, float generatorSquare, Point_2 gridCell)
{
    Polygon_2 polygon;
    // Generate new polygons until none of the extreme vertices are equal
    while (true){

        CGAL::random_polygon_2(size, std::back_inserter(polygon), Point_generator(generatorSquare));

        if (polygon.top_vertex() != polygon.right_vertex()
            && polygon.right_vertex() != polygon.bottom_vertex()
            && polygon.top_vertex() != polygon.left_vertex()
            && polygon.left_vertex() != polygon.bottom_vertex()
            && polygon.is_simple()
        ) break;

        std::cout << "Regenerating polygon, one of vertices is not cool" << std::endl;
        polygon.clear();
    }

    // points are centered around 0,0 so first move them in the first cell
    gridCell = Point_2(gridCell.x() + generatorSquare, gridCell.y() + generatorSquare);
    for (auto v = polygon.vertices_begin(); v != polygon.vertices_end(); ++v)
    {
        *v = Point_2((*v).x() + gridCell.x(), (*v).y() + gridCell.y());
    }

    /*// fix some annoyances with top/right or bottom/right vertices being the same.
    if (polygon.top_vertex() == polygon.right_vertex()){
        std::cout << "Fixed a bottom right corner" << std::endl;
        Point_2 p = *(polygon.right_vertex());
        polygon.insert(polygon.right_vertex(), Point_2(p.x() + 0.00001, p.y() -0.00001));
    }

    if (polygon.bottom_vertex() == polygon.right_vertex()){
        std::cout << "Fixed a top right corner" << std::endl;
        Point_2 p = *(polygon.right_vertex());
        polygon.insert(polygon.right_vertex(), Point_2(p.x() + 0.00001, p.y() +0.00001));
    }*/

    return polygon;
}
