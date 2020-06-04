#ifndef GRID_H
#define GRID_H

#include <Cell.h>
#include <vector>

using namespace std;

class Grid
{
    public:
        Grid(int width, int height);
        Polygon_2 Traverse();
        Polygon_2 CreatePolygon();
        void RegenerateCell(Point_2 cell);
        Polygon_2 result;

    protected:

    private:
        vector<vector<Cell>> grid;
        Generator generator;
        //Cell current;
        int width, height;

};

#endif // GRID_H
