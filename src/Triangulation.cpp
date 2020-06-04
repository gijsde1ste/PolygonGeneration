#include "Triangulation.h"

Triangulation::Triangulation() {

}

void Triangulation::Triangulate(Polygon_2 p) {

    CT ct;
    EdgeIterator ei;
    for (ei = p.edges_begin(); ei != p.edges_end(); ei++){
        ct.insert_constraint((*ei).source(), (*ei).target());
    }

    if (ct.is_valid()){
        cout << "Valid triangulation" << endl;
    }

    // Very slow way to find one triangle inside the polygon
    // Use this triangle to walk through all the triangles inside the polygon
    CT::Finite_faces_iterator source;
    for (source = ct.finite_faces_begin(); source != ct.finite_faces_end(); source++){
        Triangle t = ct.triangle(source);
        Point_2 m = CGAL::centroid(t);

        if (p.bounded_side(m) == CGAL::ON_BOUNDED_SIDE) {
            // source triangle should not be a degree-3 triangle
            // if at least one of the edges of the triangle is a constrained edge, it's fine
            bool valid = false;
            for (int i = 0; i < 3; i++){
                if (ct.is_constrained(CT::Edge(source, i))){
                    valid = true;
                }
            }

            if (valid) break;
        }
    }

    // Set in domain to false for all, sort of visited flag
    for (CT::Face_iterator fi = ct.faces_begin(); fi != ct.faces_end(); fi++){
        fi->set_in_domain(false);
    }

    dualTree.clear();
    Node node = {{source->vertex(0)->point(), source->vertex(1)->point(), source->vertex(2)->point()}, 0, -1, -1, -1, -1, -1};
    dualTree.push_back(node);

    triangulation.clear();
    stack<NodeFaceContainer> heap;
    heap.push({source, 0});
    //triangulation.push_back(ct.triangle(source));
    source->set_in_domain(true);


    while(!heap.empty()){
        NodeFaceContainer nfc = heap.top();
        CT::Face_handle curFh = nfc.fh;
        heap.pop();


        for (int i = 0; i < 3; i++){
            if (!ct.is_constrained(CT::Edge(curFh, i))){
                CT::Face_handle next = curFh->neighbor(i);
                if (!next->is_in_domain()){
                    next->set_in_domain(true);

                    Node *curNode = &dualTree[nfc.index];

                    Node nextNode = {{next->vertex(0)->point(), next->vertex(1)->point(), next->vertex(2)->point()},
                                    dualTree.size(),
                                    curNode->id,
                                    -1, -1, -1, -1
                                    };


                    if (curNode->leftChild == -1) curNode->leftChild = nextNode.id;
                    else if (curNode->rightChild == -1) curNode->rightChild = nextNode.id;

                    dualTree.push_back(nextNode);

                    heap.push({next, nextNode.id});
                    triangulation.push_back(ct.triangle(next));
                }
            }
        }
    }
}

void Triangulation::AssignPostOrder(int index){
    Node *curNode = &dualTree[index];

    if (curNode->leftChild != -1){
        AssignPostOrder(curNode->leftChild);
    }

    if (curNode->rightChild != -1){
        AssignPostOrder(curNode->rightChild);
    }

    curNode->postOrder = counter;
    counter++;
}

void Triangulation::FormatPostOrder()
{
    vector<Node> temp(dualTree.size());
    for (auto node = dualTree.begin(); node != dualTree.end(); node++)
    {
        // fix children and parent ids
        if (node->parent != -1) node->parent = dualTree[node->parent].postOrder;
        if (node->leftChild != -1) node->leftChild = dualTree[node->leftChild].postOrder;
        if (node->rightChild != -1) node->rightChild = dualTree[node->rightChild].postOrder;

        temp[node->postOrder] = *node;
    }

    dualTree = temp;
}

void Triangulation::Save(string file)
{
    // initializing tpie is necessary to use its writing capabilities
    tpie::tpie_init();

    size_t available_memory_mb = 2048;
    tpie::get_memory_manager().set_limit(available_memory_mb*1024*1024);

    tpie::file_stream<Node> out;

    out.open(file);
    out.write(dualTree.begin(), dualTree.end());
    out.close();

    tpie::tpie_finish();
}

void Triangulation::PrintDualTree(){
    for (auto node = dualTree.begin(); node != dualTree.end(); node++)
        cout << "--- " << node->id << " " << node->parent << " " << node->leftChild << " " << node->rightChild << " " << node->postOrder << endl;
}
