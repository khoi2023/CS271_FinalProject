/*
DirectedGraph.hpp
A file that contains the templated declarations for the directed graph class.
Written by: Khoi V.
*/
#include <iostream>
#include <vector>
#include "Vertex.hpp"
#include <fstream>
#include <tuple> // for std::tuple
#include <stdexcept> // for std::runtime_error
#include <limits> // for std::numeric_limits
#include <string> // for std::string
#include <utility> // for std::pair
#include "DoublyLinkedList.hpp"
#include "MinPriorityQueue.hpp"

#pragma once

using namespace std;

template <typename T>
class DirectedGraph {
    private:

    vector<Vertex<T>*> vertices; // adjacency list, which is a hash table of vertices

    public:

    // Default constructor
    DirectedGraph(void);

    // Copy constructor
    DirectedGraph(const DirectedGraph<T>& g);

    // Destructor
    ~DirectedGraph(void);

    // Assignment operator
    DirectedGraph<T>& operator=(const DirectedGraph<T>& g);

    // Add and remove vertices and edges
    void addVertex(Vertex<T>* v);

    void removeVertex(Vertex<T>* v);

    // Add an edge from vertex u to vertex v with weight w and name
    void addEdge(Vertex<T>* u, Vertex<T>* v, double w = 1.0, string name = "");

    // Remove an edge from vertex u to vertex v
    void removeEdge(Vertex<T>* u, Vertex<T>* v);

    // Accessor methods
    vector<Vertex<T>*> getVertices(void) const;

    vector<tuple <Vertex<T>*, double, string>> getAdjacencyList(Vertex<T>* v) const;

    // Read and write graph from a file
    DirectedGraph<T> readFromFile(const string& filename) const;

    // Dijkstra's algorithm for shortest paths
    DoublyLinkedList<pair<Vertex<T>*, double>> Dijkstra(Vertex<T>* startVertex) const;

};

#include "DirectedGraph.tpp"