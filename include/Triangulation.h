#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <Generator.h>
#include <tpie/file_stream.h>
#include <tpie/stack.h>

struct Node
{
    Point_2 points[3];
    int id, parent;
    int leftChild, rightChild;
    int postOrder, preOrder;
};

struct NodeFaceContainer
{
    CT::Face_handle fh;
    int index;
};

class Triangulation
{
    public:
        Triangulation();

        void Triangulate(Polygon_2 p);
        void AssignPostOrder(int index);
        void FormatPostOrder();
        void PrintDualTree();
        void Save(string file);

        vector<Triangle> triangulation;
        vector<Node> dualTree;

    protected:

    private:
        int counter = 0;

};

#endif // TRIANGULATION_H
