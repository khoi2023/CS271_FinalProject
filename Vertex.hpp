/*
Vertex.hpp
This file defines a Vertex class template for use in graph algorithms.
The Vertex class represents a vertex in a graph and contains methods for managing its properties and edges.
It includes methods for setting and getting the vertex value, visited status, distance, finish time, parent vertex, and adjacency list.
The class also provides methods for adding and removing edges to the adjacency list.
It is designed to be used with various data types, as indicated by the template parameter T.
Written by: Duc T.
*/

#include <iostream>
#include <vector>
#include <utility> // for std::pair
#include <tuple> // for std::tuple
#include <stdexcept> // for std::runtime_error
#include <limits> // for std::numeric_limits
#include <string> // for std::string

#pragma once

using namespace std;

template <typename T>
class Vertex {
    private:
    T value;
    bool visited = false;
    double distance = numeric_limits<double>::infinity();
    int finishTime;
    Vertex<T>* parent = nullptr;
    vector<tuple <Vertex<T>*, double, string>> adjacencyList; // adjacency list for the vertex

    public:
    // Default constructor
    Vertex(T val);

    // Copy constructor
    Vertex(const Vertex<T>& v);

    // Assignment operator
    Vertex<T>& operator=(const Vertex<T>& v);

    // Destructor
    ~Vertex();

    // Accessor and mutator methods
    T getValue();

    void setValue(T val);

    bool isVisited();

    void setVisited(bool v);

    double getDistance();

    void setDistance(double d);

    int getFinishTime();

    void setFinishTime(int time);

    Vertex<T>* getParent();

    void setParent(Vertex<T>* p);

    // Add and remove edges to the adjacency list
    void addEdge(Vertex<T>* v, double w = 1.0, string name = "");

    void removeEdge(Vertex<T>* v);

    // Getters for adjacency list
    vector<tuple <Vertex<T>*, double, string>>& getAdjacencyList();
};

#include "Vertex.tpp"