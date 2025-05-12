/*
studentTests.cpp
This file contains a set of unit tests for the DirectedGraph class and its associated Vertex class.
Written by: Khoi V.
*/
#include <cassert>
#include <iostream>
#include <cmath>   // for fabs
#include <fstream>
#include <vector>
#include "DirectedGraph.hpp"
#include "Vertex.hpp"

using namespace std;

int main() {
    // 1) test addVertex + getVertices
    DirectedGraph<int> g;
    Vertex<int>* v1 = new Vertex<int>(1);
    Vertex<int>* v2 = new Vertex<int>(2);
    g.addVertex(v1);
    g.addVertex(v2);
    vector<Vertex<int>*> verts = g.getVertices();
    assert(verts.size() == 2);
    assert(verts[0]->getValue() == 1);
    assert(verts[1]->getValue() == 2);

    // 2) test addEdge + getAdjacencyList
    g.addEdge(v1, v2, 5.0, "Edge1");
    auto adjList = g.getAdjacencyList(v1);
    assert(adjList.size() == 1);
    assert(get<0>(adjList[0]) == v2);
    assert(get<1>(adjList[0]) == 5.0);
    assert(get<2>(adjList[0]) == "Edge1");
    
    // 3) test removeEdge
    g.removeEdge(v1, v2);
    adjList = g.getAdjacencyList(v1);
    assert(adjList.size() == 0);
    
    // 4) test removeVertex (ignore exceptions from missing edges)
    try {
        g.removeVertex(v1);
    } catch (const runtime_error&) {
        // ok if no edge to remove
    }
    verts = g.getVertices();
    assert(verts.size() == 1);
    assert(verts[0]->getValue() == 2);

    try {
        g.removeVertex(v2);
    } catch (const runtime_error&) {
        // ok if no edge to remove
    }
    verts = g.getVertices();
    assert(verts.size() == 0);
    
    // 5) test readFromFile (with multi-word edge names) and Dijkstra
    const string fname = "temp_graph.txt";
    ofstream ofs(fname);
    // 3 vertices, 3 edges
    ofs << "3 3\n";
    ofs << "0 0.0 0.0\n";
    ofs << "1 1.0 1.0\n";
    ofs << "2 2.0 2.0\n";
    // each name has spaces
    ofs << "0 1 1.5 Edge A street\n";
    ofs << "1 2 2.5 ['Edge B road', 'Edge B avenue']\n";
    ofs << "2 0 3.5 Edge C avenue\n";
    ofs.close();

    DirectedGraph<int> g3 = DirectedGraph<int>().readFromFile(fname);
    auto verts3 = g3.getVertices();
    assert(verts3.size() == 3);

    // verify adjacency & full edge name
    auto adj0 = g3.getAdjacencyList(verts3[0]);
    assert(adj0.size() == 1);
    assert(get<0>(adj0[0]) == verts3[1]);
    assert(fabs(get<1>(adj0[0]) - 1.5) < 1e-6);
    assert(get<2>(adj0[0]) == "Edge A street");

    // run Dijkstra from vertex 0:
    // distances: 0→0=0, 0→1=1.5, 0→2=1.5+2.5=4.0
    auto path = g3.Dijkstra(verts3[0]);
    assert(path.size() == 3);
    assert(path[0].first == verts3[0] && fabs(path[0].second - 0.0) < 1e-6);
    assert(path[1].first == verts3[1] && fabs(path[1].second - 1.5) < 1e-6);
    assert(path[2].first == verts3[2] && fabs(path[2].second - 4.0) < 1e-6);

    remove(fname.c_str());
    cout << "All DirectedGraph tests passed.\n";
    return 0;
}