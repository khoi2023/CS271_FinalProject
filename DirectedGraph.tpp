/*
DirectedGraph.tpp
A file that contains the implementation of the DirectedGraph class methods.
Written by: Khoi V.
*/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <limits> // for std::numeric_limits
#include "DirectedGraph.hpp"

using namespace std;

// Default constructor.
// Initializes an empty directed graph.
// Parameters: None.
// Return value: None.
template <typename T>
DirectedGraph<T>::DirectedGraph(void) {
    
}

// Copy constructor.
// Creates a deep copy of the given directed graph, including all vertices and edges.
// Parameters: g - the directed graph to copy.
// Return value: None.
template <typename T>
DirectedGraph<T>::DirectedGraph(const DirectedGraph<T>&g) {
    // 1) clone all vertices and build a remapping
    unordered_map<Vertex<T>*,Vertex<T>*> remap;
    remap.reserve(g.vertices.size());
    for (auto v : g.vertices) {
        Vertex<T>* v2 = new Vertex<T>(*v);
        vertices.push_back(v2);
        remap[v] = v2;
    }
    // 2) clone all edges using that map
    for (auto v : g.vertices) {
        Vertex<T>* v2 = remap[v];
        for (auto &e : v->getAdjacencyList()) {
            Vertex<T>* oldNbr = get<0>(e);
            double       w     = get<1>(e);
            string       name  = get<2>(e);
            v2->addEdge(remap[oldNbr], w, name);
        }
    }
}

// Destructor.
// Cleans up all vertices in the directed graph.
// Parameters: None.
// Return value: None.
template <typename T>
DirectedGraph<T>::~DirectedGraph(void) {
    for (Vertex<T>* v : vertices) {
        delete v;
    }
}

// Assignment operator.
// Implements the copy-and-swap idiom to create a deep copy of the given directed graph.
// Parameters: g - the directed graph to copy.
// Return value: A reference to the current directed graph object.
// Note: This method uses the copy-and-swap idiom to ensure exception safety.
template <typename T>
DirectedGraph<T>& DirectedGraph<T>::operator=(const DirectedGraph<T>& g) {
    if (this != &g) {
        // clean up current
        for (auto v : vertices) delete v;
        vertices.clear();
        // same two‐step copy as above
        unordered_map<Vertex<T>*,Vertex<T>*> remap;
        remap.reserve(g.vertices.size());
        for (auto v : g.vertices) {
            Vertex<T>* v2 = new Vertex<T>(*v);
            vertices.push_back(v2);
            remap[v] = v2;
        }
        for (auto v : g.vertices) {
            Vertex<T>* v2 = remap[v];
            for (auto &e : v->getAdjacencyList()) {
                v2->addEdge(remap[get<0>(e)], get<1>(e), get<2>(e));
            }
        }
    }
    return *this;
}

// Add a vertex to the directed graph.
// Parameters: v - the vertex to add.
// Return value: None.
template <typename T>
void DirectedGraph<T>::addVertex(Vertex<T>* v) {
    vertices.push_back(v);
}

// Remove a vertex from the directed graph.
// Parameters: v - the vertex to remove.
// Return value: None.
// Note: This method also removes all edges to this vertex from other vertices.
// It throws an exception if the vertex does not exist in the graph.
template <typename T>
void DirectedGraph<T>::removeVertex(Vertex<T>* v) {
    typename std::vector<Vertex<T>*>::iterator it = vertices.begin();
    while (it != vertices.end()) {
        if (*it == v) {
            delete *it;
            it = vertices.erase(it);
            break;
        } else {
            ++it;
        }
    }
    // Remove all edges to this vertex from other vertices
    for (Vertex<T>* vertex : vertices) {
        vertex->removeEdge(v);
    }
}

// Add an edge from vertex u to vertex v with weight w and name.
// Parameters: u - the source vertex, v - the destination vertex, w - the weight of the edge, name - the name of the edge.
// Return value: None.
template <typename T>
void DirectedGraph<T>::addEdge(Vertex<T>* u, Vertex<T>* v, double w, string name) {
    u->addEdge(v, w, name);
}

// Remove an edge from vertex u to vertex v.
// Parameters: u - the source vertex, v - the destination vertex.
// Return value: None.
// Note: This method throws an exception if the edge does not exist.
template <typename T>
void DirectedGraph<T>::removeEdge(Vertex<T>* u, Vertex<T>* v) {
    // Throw an exception if edge does not exist
    if (u->getAdjacencyList().empty()) {
        throw runtime_error("Edge does not exist");
    }
    u->removeEdge(v);
}

// Accessor method to get the list of vertices in the directed graph.
// Parameters: None.
// Return value: A vector of pointers to the vertices in the directed graph.
template <typename T>
vector<Vertex<T>*> DirectedGraph<T>::getVertices(void) const {
    return vertices;
}

// Accessor method to get the adjacency list of a vertex.
// Parameters: v - the vertex whose adjacency list to retrieve.
// Return value: A vector of tuples containing the adjacent vertices, their weights, and edge names.
template <typename T>
vector<tuple <Vertex<T>*, double, string>> DirectedGraph<T>::getAdjacencyList(Vertex<T>* v) const {
    return v->getAdjacencyList();
}

// Read a directed graph from a file.
// Parameters: filename - the name of the file to read from.
// Return value: A DirectedGraph object representing the graph read from the file.
template <typename T>
DirectedGraph<T> DirectedGraph<T>::readFromFile(const string& filename) const {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }

    int n, m;
    file >> n >> m; // Read the number of vertices and edges

    DirectedGraph<T> graph;

    // Read vertices and create them
    unordered_map<size_t,Vertex<T>*> idToVertex;
    idToVertex.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        size_t vid;
        double x,y;
        file >> vid >> x >> y;
        Vertex<T>* vertex = new Vertex<T>( static_cast<T>(vid) );
        graph.addVertex(vertex);
        idToVertex[vid] = vertex;
    }

    // Read edges and add them to the graph
    for (size_t i = 0; i < m; ++i) {
        size_t uid, vid;
        double weight;
        file >> uid >> vid >> weight;
        string edgeName;
        getline(file >> ws, edgeName);
        auto uPtr = idToVertex.at(uid);
        auto vPtr = idToVertex.at(vid);
        graph.addEdge(uPtr, vPtr, weight, edgeName);
    }

    // Close the file
    file.close();
    return graph;
}

// Dijkstra's Algorithm
// Description: Computes the shortest paths from the start vertex to all other vertices in the directed graph using Dijkstra's algorithm.
// It returns a list of pairs where each pair contains a vertex and its distance from the start vertex.
// The algorithm uses a min-priority queue to efficiently find the vertex with the smallest distance.
// Parameters: startVertex - the vertex from which to compute the shortest paths.
// Return value: A DoublyLinkedList of pairs, where each pair contains a vertex and its distance from the start vertex.
// Note: The function assumes that the graph is connected and that all edge weights are positive.
// It throws an exception if the start vertex is not found in the graph.
template <typename T>
DoublyLinkedList<pair<Vertex<T>*, double>> DirectedGraph<T>::Dijkstra(Vertex<T>* startVertex) const {
    // 1) initialize all vertices
    for (auto v : vertices) {
        v->setDistance(numeric_limits<double>::infinity());
        v->setParent(nullptr);
        v->setVisited(false);
    }
    // find the actual start vertex in our list
    Vertex<T>* actualStart = nullptr;
    for (auto v : vertices) {
        if (v == startVertex || v->getValue() == startVertex->getValue()) {
            actualStart = v;
            break;
        }
    }
    if (!actualStart) {
        throw runtime_error("Start vertex not found in the graph.");
    }
    actualStart->setDistance(0.0);

    // 2) build min-PQ<distance, vertex>
    minPQ<double, Vertex<T>*> pq(vertices.size());
    for (auto v : vertices) {
        pq.insert(v->getDistance(), v);
    }

    // 3) extract-min and relax
    while (!pq.empty()) {
        auto [du, u] = pq.pop();
        // once the min distance is infinity, all remaining are unreachable
        if (du == numeric_limits<double>::infinity()) break;
        // skip stale entries or already finalized nodes
        if (u->isVisited()) continue;

        u->setVisited(true);
        // relax each outgoing edge
        for (auto &e : u->getAdjacencyList()) {
            Vertex<T>* nbr = get<0>(e);
            double      w   = get<1>(e);
            // only relax if neighbor still in queue
            if (!nbr->isVisited()) {
                double alt = du + w;
                if (alt < nbr->getDistance()) {
                    nbr->setDistance(alt);
                    nbr->setParent(u);
                    pq.updateKey(alt, nbr);
                }
            }
        }
    }

    // 4) collect distances into a list
    DoublyLinkedList<pair<Vertex<T>*, double>> out;
    for (auto v : vertices) {
        out.push_back(make_pair(v, v->getDistance()));
    }
    return out;
}