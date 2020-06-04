#include "Cell.h"
#include <iostream>
#include <Renderer.h>

Cell::Cell(Point_2 cell, Generator generator)
{
    x = cell.x();
    y = cell.y();
    std::cout << cell << std::endl;

    polygon = generator.GeneratePolygon(200, 0.45, cell);
}

void Cell::ConcatenateStartRow(Cell next, Polygon_2 &result){


    auto rightVertex = polygon.right_vertex();
    Point_2 newRightVertex = Point_2((*rightVertex).x(), (*rightVertex).y() - 0.0000000001);
    polygon.insert(rightVertex, newRightVertex);

    Point_2 top = *std::next(polygon.bottom_vertex());
    Point_2 right = newRightVertex;

    AddVertices(top, right, result);

    result.push_back(*next.polygon.left_vertex());

}

void Cell::ConcatenateLeftRight(Cell next, Polygon_2 &result){

    auto rightVertex = polygon.right_vertex();
    Point_2 newRightVertex = Point_2((*rightVertex).x(), (*rightVertex).y() - 0.0000000001);
    polygon.insert(rightVertex, newRightVertex);

    Point_2 left = *(std::next(polygon.left_vertex()));
    Point_2 right = newRightVertex;

    AddVertices(left, right, result);

    // Link polygon to left most vertex of next polygon
    result.push_back(*next.polygon.left_vertex());
}

void Cell::ConcatenateRightTurn(Cell next, Polygon_2 &result){

    auto leftVertex = polygon.left_vertex();
    Point_2 newLeftVertex = Point_2((*leftVertex).x(), (*leftVertex).y() + 0.0000000001);
    polygon.insert(leftVertex, newLeftVertex);

    Point_2 left = *(std::next(polygon.left_vertex()));

    // Full Polygon + first of the polygon to the left
    AddVertices(left, newLeftVertex, result);
    result.push_back(*next.polygon.right_vertex());
}

void Cell::ConcatenateRightLeft(Cell next, Polygon_2 &result){

    auto leftVertex = polygon.left_vertex();
    Point_2 newLeftVertex = Point_2((*leftVertex).x(), (*leftVertex).y() + 0.0000000001);
    polygon.insert(leftVertex, newLeftVertex);

    Point_2 right = *(std::next(polygon.right_vertex()));

    // Add vertices from right to left and add right most of next polygon
    AddVertices(right, newLeftVertex, result);
    result.push_back(*next.polygon.right_vertex());
}

void Cell::ConcatenateUpTurn(Cell next, Polygon_2 &result){

    auto topVertex = polygon.bottom_vertex();
    Point_2 newTopVertex = Point_2((*topVertex).x() - 0.0000000001, (*topVertex).y());
    polygon.insert(topVertex, newTopVertex);

    Point_2 right = *(std::next(polygon.right_vertex()));

    // Add vertices from right to top and add bottom most of next polygon
    AddVertices(right, newTopVertex, result);
    result.push_back(*next.polygon.top_vertex());
}

void Cell::ConcatenateDownTurn(Cell next, Polygon_2 &result){

    auto bottomVertex = polygon.top_vertex();
    Point_2 newBottomVertex = Point_2((*bottomVertex).x() + 0.0000000001, (*bottomVertex).y() - 0.00000000001);
    polygon.insert(bottomVertex, newBottomVertex);

    Point_2 right = *(std::next(polygon.right_vertex()));

    // Add vertices from right to bottom and add top most of next polygon
    AddVertices(right, newBottomVertex, result);
    result.push_back(*next.polygon.bottom_vertex());
}

void Cell::ConcatenateBottemUp(Cell next, Polygon_2 &result){

    auto topVertex = polygon.bottom_vertex();
    Point_2 newTopVertex = Point_2((*topVertex).x() - 0.0000000001, (*topVertex).y());
    polygon.insert(topVertex, newTopVertex);

    Point_2 bottom = *(std::next(polygon.top_vertex()));

    // Add vertices from bottom to top and add bottom most of next polygon
    AddVertices(bottom, newTopVertex, result);
    result.push_back(*next.polygon.top_vertex());
}

void Cell::ConcatenateTopLeft(Polygon_2 &result){

    Point_2 bottom = *(std::next(polygon.top_vertex()));
    Point_2 top = *(polygon.bottom_vertex());

    // Add vertices from bottom to top
    AddVertices(bottom, top, result);
}

void Cell::AddVertices(Point_2 from, Point_2 to, Polygon_2 &result)
{
    bool fromFound = false;
    bool toFound = false;

    for (auto vi = polygon.vertices_begin(); vi != polygon.vertices_end(); ++vi)
    {
        if (*vi == from) fromFound = true;

        if (fromFound && !toFound){
            result.push_back(*vi);
        }

        if (*vi == to && fromFound) toFound = true;
    }

    if (!toFound) {
        for (auto vi = polygon.vertices_begin(); vi != polygon.vertices_end(); ++vi)
        {
            result.push_back(*vi);

            if (*vi == to) break;
        }
    }
}
