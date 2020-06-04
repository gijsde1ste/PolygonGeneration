#ifndef CELL_H
#define CELL_H

#include <Generator.h>

class Cell
{
    public:
        Cell(Point_2 cell, Generator generator);
        Polygon_2 polygon;
        int x, y;

        void ConcatenateStartRow(Cell next, Polygon_2 &result);
        void ConcatenateLeftRight(Cell next, Polygon_2 &result);
        void ConcatenateRightTurn(Cell next, Polygon_2 &result);
        void ConcatenateRightLeft(Cell next, Polygon_2 &result);
        void ConcatenateUpTurn(Cell next, Polygon_2 &result);
        void ConcatenateDownTurn(Cell next, Polygon_2 &result);
        void ConcatenateBottemUp(Cell next, Polygon_2 &result);
        void ConcatenateTopLeft(Polygon_2 &result);

        void AddVertices(Point_2 from, Point_2 to, Polygon_2 &result);

    protected:

    private:
};

#endif // CELL_H
