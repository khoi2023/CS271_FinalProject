/*
Vertex.tpp
This file contains the implementation of the Vertex class template.
The Vertex class represents a vertex in a graph and includes methods for managing its properties and edges.
It includes methods for setting and getting the vertex value, visited status, distance, finish time, parent vertex, and adjacency list.
The class also provides methods for adding and removing edges to the adjacency list.
It is designed to be used with various data types, as indicated by the template parameter T.
Written by: Duc T.
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "Vertex.hpp"

using namespace std;

// Default constructor
// Initializes the vertex with a value and sets default properties
// Parameters: - val: The value to be assigned to the vertex.
// The default properties are: visited = false, distance = 0.0, parent = nullptr, finishTime = 0.
// Return value: None.
template <typename T>
Vertex<T>::Vertex(T val) {
    value = val;
    visited = false;
    distance = 0.0;
    parent = nullptr;
    finishTime = 0;
}

// Copy constructor
// Initializes a new vertex as a copy of an existing vertex.
// Parameters: - v: The vertex to be copied.
// The new vertex will have the same properties as the copied vertex.
// Return value: None.
template <typename T>
Vertex<T>::Vertex(const Vertex<T>& v) {
    value = v.value;
    visited = v.visited;
    distance = v.distance;
    parent = v.parent;
    finishTime = v.finishTime;
}

// Assignment operator
// Assigns the properties of one vertex to another vertex.
// Parameters: - v: The vertex to be assigned.
// The current vertex will take on the properties of the assigned vertex.
// Return value: A reference to the current vertex.
// This allows for chaining of assignment operations.
template <typename T>
Vertex<T>& Vertex<T>::operator=(const Vertex<T>& v) {
    if (this != &v) {
        value = v.value;
        visited = v.visited;
        distance = v.distance;
        parent = v.parent;
        finishTime = v.finishTime;
    }
    return *this;
}

// Destructor
// Cleans up the vertex when it is no longer needed.
// Parameters: None.
// Return value: None.
// The destructor does not need to do anything special in this case,
// as the vertex does not manage any dynamic memory.
template <typename T>
Vertex<T>::~Vertex(void) {

}

// Accessor and mutator methods

// Get the value of the vertex
// Parameters: None.
// Return value: The value of the vertex.
template <typename T>
T Vertex<T>::getValue() {
    return value;
}

// Set the value of the vertex
// Parameters: - val: The value to be assigned to the vertex.
// Return value: None.
template <typename T>
void Vertex<T>::setValue(T val) {
    value = val;
}

// Check if the vertex has been visited
// Parameters: None.
// Return value: true if the vertex has been visited, false otherwise.
template <typename T>
bool Vertex<T>::isVisited() {
    return visited;
}

// Set the visited status of the vertex
// Parameters: - v: The visited status to be assigned to the vertex.
// Return value: None.
template <typename T>
void Vertex<T>::setVisited(bool v) {
    visited = v;
}

// Get the distance from the source vertex
// Parameters: None.
// Return value: The distance from the source vertex.
template <typename T>
double Vertex<T>::getDistance() {
    return distance;
}

// Set the distance from the source vertex
// Parameters: - d: The distance to be assigned to the vertex.
// Return value: None.
template <typename T>
void Vertex<T>::setDistance(double d) {
    distance = d;
}

// Get the finish time of the vertex
// Parameters: None.
// Return value: The finish time of the vertex.
template <typename T>
int Vertex<T>::getFinishTime() {
    return finishTime;
}

// Set the finish time of the vertex
// Parameters: - time: The finish time to be assigned to the vertex.
// Return value: None.
template <typename T>
void Vertex<T>::setFinishTime(int time) {
    finishTime = time;
}

// Get the parent vertex
// Parameters: None.
// Return value: A pointer to the parent vertex.
// If the parent is null, it indicates that the vertex has no parent.
template <typename T>
Vertex<T>* Vertex<T>::getParent() {
    if (parent == nullptr) {
        return nullptr;
    }
    return parent;
}

// Set the parent vertex
// Parameters: - p: A pointer to the parent vertex to be assigned.
// Return value: None.
template <typename T>
void Vertex<T>::setParent(Vertex<T>* p) {
    parent = p;
}

// Add an edge from this vertex to another vertex
// (i.e., add the other vertex to this vertex's adjacency list)
// Parameters: - v: A pointer to the vertex to be added.
// - w: The weight of the edge (default is 1.0).
// - name: The name of the edge (default is an empty string).
// Return value: None.
// The adjacency list is a vector of tuples, where each tuple contains the inbound vertex,
// the weight of the edge, and the name of the edge.
template <typename T>
void Vertex<T>::addEdge(Vertex<T>* v, double w, string name) {
    adjacencyList.push_back(tuple<Vertex<T>*, double, string>(v, w, name));
}

// Remove an edge from this vertex to another vertex
// (i.e., remove the other vertex from this vertex's adjacency list)
// Parameters: - v: A pointer to the vertex to be removed.
// Return value: None.
// If the edge does not exist, an exception is thrown.
template <typename T>
void Vertex<T>::removeEdge(Vertex<T>* v) {
    // Throw an exception if edge does not exist
    if (adjacencyList.empty()) {
        throw runtime_error("Edge does not exist");
    }
    typename vector<tuple <Vertex<T>*, double, string>>::iterator it = adjacencyList.begin();
    while (it != adjacencyList.end()) {
        if (get<0>(*it) == v) {
            adjacencyList.erase(it);
            break;
        }
        ++it;
    }
}

// Get the adjacency list of the vertex
// Parameters: None.
// Return value: A reference to the adjacency list of the vertex.
template <typename T>
vector<tuple <Vertex<T>*, double, string>>& Vertex<T>::getAdjacencyList() {
    return adjacencyList;
}