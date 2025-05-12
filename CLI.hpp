/*
CLI.hpp
A file that contains the declaration of the GraphMap class for handling user input and output in the CLI route planner.
Written by: Khoi V.
*/
#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "DirectedGraph.hpp"
#include "Vertex.hpp"

using namespace std;

class GraphMap {
private:
    // Graph representation
    // The graph is represented as a directed graph with vertices of type size_t
    DirectedGraph<size_t> G;
    // Maps to store vertex IDs, coordinates, and names
    // ID[x][y] = id, where id is the vertex ID for coordinates (x,y)
    unordered_map<double, unordered_map<double, size_t>> ID;
    // Coor[id] = (x,y), where id is the vertex ID and (x,y) are the coordinates
    unordered_map<size_t, pair<double,double>> Coor;
    // Name[u][v] = name, where u and v are vertex IDs and name is the edge name
    // This is used to store the names of edges between vertices u and v
    unordered_map<size_t, unordered_map<size_t,string>> Name;
    // Maps to store vertex pointers
    // vertexMap[id] = vertex pointer, where id is the vertex ID and vertex pointer is a pointer to the Vertex object
    unordered_map<size_t, Vertex<size_t>*> vertexMap;

public:
    // Loads the graph from a file
    bool load_file();
    // Gets the start and end coordinates from the user
    void get_coordinates(double &sx, double &sy, double &ex, double &ey);
    // Validates the input coordinates
    // Checks if the start and end coordinates are valid
    bool validate_input(double sx, double sy, double ex, double ey);
    // Finds the shortest path between the start and end coordinates
    // Uses Dijkstra's algorithm to find the shortest path
    // Prints the shortest path and turn-by-turn directions
    void find_path();
    // Quits the program
    void quit();
};

#include "CLI.tpp"
