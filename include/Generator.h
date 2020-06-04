#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/random_polygon_2.h>
#include <CGAL/Polygon_2_algorithms.h>
#include <CGAL/Polygon_2.h>

#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Delaunay_mesh_face_base_2.h>
#include <CGAL/Delaunay_mesh_vertex_base_2.h>
#include <CGAL/Partition_traits_2.h>
#include <CGAL/partition_2.h>
#include <CGAL/centroid.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel         K;
typedef K::Point_2                                                  Point_2;
typedef std::list<Point_2>                                          Container;
typedef CGAL::Polygon_2<K, Container>                               Polygon_2;
typedef CGAL::Random_points_in_square_2< Point_2 >                  Point_generator;
typedef typename Container::iterator                                Vertex_const_iterator;

typedef CGAL::Delaunay_mesh_vertex_base_2<K>                        Vb;
typedef CGAL::Delaunay_mesh_face_base_2<K>                          Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb>                TDS;
typedef CGAL::Exact_predicates_tag                                  Itag;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, TDS, Itag>    CT;

typedef CGAL::Partition_traits_2<K>                                 Traits;
typedef CGAL::Triangle_2<K>                                         Triangle;
typedef Polygon_2::Edge_const_iterator                              EdgeIterator;

class Generator
{
    public:
        Generator();
        Polygon_2 GeneratePolygon(int size, float generatorSquare, Point_2 gridCell);

    protected:

    private:
};

#endif // GENERATOR_H
