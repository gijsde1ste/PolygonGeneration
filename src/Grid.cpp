#include "Grid.h"
#include <iostream>

Grid::Grid(int width, int height)
{
    this->width = width;
    this->height = height;

    //Polygon_2 result;
    Generator generator;
    for (int x = 0; x < width; ++x)
    {
        vector<Cell> column;
        for (int y = 0; y < height; ++y)
        {
            column.push_back(Cell(Point_2(x,y), generator));
        }
        grid.push_back(column);
    }
}

Polygon_2 Grid::CreatePolygon()
{
    // Create polygon by traversing the entire grid
    result = Traverse();

    // Fix rare mistakes when moving vertexes causes edges to intersect
    while (!result.is_simple()) {

        std::pair<std::ptrdiff_t,std::ptrdiff_t> conflictPair =
        CGAL::check_simple_polygon(
            result.vertices_begin(),
            result.vertices_end(),
            result.traits_member()
        );

        auto a = result.vertices_begin();
        std::advance(a, conflictPair.first+1);

        auto b = a;
        std::advance(b, conflictPair.second-conflictPair.first);

        Point_2 v = Point_2(floor((*a).x()), floor((*a).y()));
        Point_2 w = Point_2(floor((*b).x()), floor((*b).y()));

        cout << "Issue in cell " << v << " and " << w << endl;

        RegenerateCell(v);
        RegenerateCell(w);

        // First clear the result or polygon gets messy
        result.clear();
        result = Traverse();
    }

    cout << "SUCCESS" << endl;

    return result;
}

Polygon_2 Grid::Traverse()
{
    cout << "Traversing" << endl;
    // top to bottom
    for (int y = 0; y < height; ++y){
        // start row, enters from top and goes to right
        grid[0][y].ConcatenateStartRow(grid[1][y], result);

        // left to right
        for (int x = 2; x < width; ++x){
            grid[x - 1][y].ConcatenateLeftRight(grid[x][y], result);
        }

        // turn at end of row
        grid[width - 1][y].ConcatenateRightTurn(grid[width - 2][y], result);

        // right to left
        for (int x = width - 2; x > 0; --x){
            grid[x][y].ConcatenateRightLeft(grid[x - 1][y], result);
        }

        if (y == height - 1) {
            // Last row, make corner and go back up
            grid[0][y].ConcatenateUpTurn(grid[0][height - 2], result);
        } else {
            // Not last row, make corner and proceed next row
            grid[0][y].ConcatenateDownTurn(grid[0][y + 1], result);
        }

    }

    // bottom to top
    for (int y = height - 2; y > 0; --y){
        grid[0][y].ConcatenateBottemUp(grid[0][y-1], result);
    }

    // finish up by concatenating last bit, top left corner
    grid[0][0].ConcatenateTopLeft(result);

    return result;
}

void Grid::RegenerateCell(Point_2 cell){
    grid[cell.x()][cell.y()] = Cell(cell, generator);
}
