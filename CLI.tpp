/*
CLI.tpp
A file that contains the implementation of the GraphMap class for handling user input and output in the CLI route planner.
Written by: Khoi V, Duc T.
*/
#include "CLI.hpp"
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <algorithm>
#include <cmath>

// Function to load the graph from a file
// Parameters: None.
// Return value: true if the graph is successfully loaded, false otherwise.
// If the user enters 'q', the program quits.
// If it fails to open the file, an error message is displayed and the user is prompted to try again.
// Written by: Duc T.
bool GraphMap::load_file() {
    string file_name;
    cout << "Enter a file name to load, or press 'q' to quit: ";
    cin >> file_name;
    if (file_name == "q") quit();
    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return false;
    }

    // Read the number of vertices and edges
    size_t n,m;
    file >> n >> m;
    // Read vertices and create them
    for (size_t i = 0; i < n; ++i) {
        size_t id; double x,y;
        file >> id >> x >> y;
        ID[x][y] = id;
        Coor[id]  = {x,y};
        auto v = new Vertex<size_t>(id);
        G.addVertex(v);
        vertexMap[id] = v;
    }
    file.ignore(numeric_limits<streamsize>::max(), '\n');
    // Read edges and add them to the graph
    for (size_t i = 0; i < m; ++i) {
        size_t u,v; double w;
        file >> u >> v >> w;
        string s;
        if (file.peek()==' ') {
            file.get();
            getline(file,s);
        }
        Name[u][v] = s;
        G.addEdge(vertexMap[u], vertexMap[v], w, s);
    }
    file.close();
    cout << "Graph successfully loaded!" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

// Function to get start and end coordinates from the user
// Parameters: sx, sy - start coordinates; ex, ey - end coordinates.
// Return value: None.
// The function prompts the user to enter coordinates and validates the input.
// If the input is invalid, it continues to prompt until valid coordinates are entered.
// Written by: Duc T.
void GraphMap::get_coordinates(double &sx,double &sy,double &ex,double &ey) {
    string line; stringstream ss;
    while (true) {
        cout << "Enter start coordinates: ";
        getline(cin,line);
        if (line=="q") quit();
        ss.clear(); ss.str(line);
        if (ss>>sx>>sy && ss.eof()) break;
        cerr<<"Invalid input. Please try again."<<endl;
    }
    while (true) {
        cout << "Enter end coordinates: ";
        getline(cin,line);
        if (line=="q") quit();
        ss.clear(); ss.str(line);
        if (ss>>ex>>ey && ss.eof()) break;
        cerr<<"Invalid input. Please try again."<<endl;
    }
}

// Function to validate the input coordinates
// Parameters: sx, sy - start coordinates; ex, ey - end coordinates.
// Return value: true if the coordinates are valid, false otherwise.
// Written by: Duc T.
bool GraphMap::validate_input(double sx,double sy,double ex,double ey) {
    if (ID.find(sx)==ID.end() || ID[sx].find(sy)==ID[sx].end()) {
        cerr<<"Error: Start ("<<sx<<","<<sy<<") not valid!"<<endl;
        return false;
    }
    if (ID.find(ex)==ID.end() || ID[ex].find(ey)==ID[ex].end()) {
        cerr<<"Error: End ("<<ex<<","<<ey<<") not valid!"<<endl;
        return false;
    }
    return true;
}

// Function to find the shortest path using Dijkstra's algorithm
// Parameters: None.
// Return value: None.
// Written by: Khoi V.
void GraphMap::find_path() {
    double sx,sy,ex,ey;
    // Get start and end coordinates from the user
    // Validate the input coordinates
    do {
        get_coordinates(sx,sy,ex,ey);
    } while (!validate_input(sx,sy,ex,ey));

    // Get vertex IDs for start and end coordinates
    size_t sid = ID[sx][sy], eid = ID[ex][ey];
    auto startV = vertexMap[sid], endV = vertexMap[eid];

    // Perform Dijkstra's algorithm
    // Find the shortest path from startV to all other vertices
    G.Dijkstra(startV);
    double dist = endV->getDistance();
    if (dist== numeric_limits<double>::infinity()) {
        cout<<"No path found!"<<endl;
        return;
    }

    // Backtrack to find the route
    vector<size_t> route;
    for (auto cur=endV; cur; cur=cur->getParent())
        route.push_back(cur->getValue());
    reverse(route.begin(),route.end());

    // Build coordinate list
    vector<pair<double,double>> pts;
    for (auto id : route) pts.push_back(Coor[id]);

    // Print shortest route
    cout<<"Shortest path from ("<<sx<<","<<sy<<") to ("<<ex<<","<<ey<<") is: "<<endl;
    for (size_t i=0;i<route.size();++i) {
        auto [x,y] = Coor[route[i]];
        cout<<"("<<x<<","<<y<<")";
        if (i+1<route.size()) {
            cout<<" -> ";
            auto nm = Name[route[i]][route[i+1]];
            if (!nm.empty()) cout<<"("<<nm<<") -> "<<endl;
        }
    }

    cout << endl;

    // Print turn-by-turn directions
    cout<<"Turn-by-turn directions:"<<endl;
    if (route.size() > 1) {
        // Initial street
        string street = Name[route[0]][route[1]];
        cout<<"  Start on "<< (street.empty()?"<unnamed road>":street) <<endl;
    }

    // Compute turn directions
    auto turnType = [&](auto &A, auto &B){
        // cross = Ax*By - Ay*Bx
        double cross = A.first*B.second - A.second*B.first;
        if (fabs(cross) < 1e-6) return "Continue straight";
        return (cross>0 ? "Turn left":"Turn right");
    };

    // Iterate through points to determine turns and print directions
    for (size_t i = 1; i+1 < pts.size(); ++i) {
        auto &P0 = pts[i-1], &P1 = pts[i], &P2 = pts[i+1];
        pair<double,double> A{P1.first-P0.first, P1.second-P0.second};
        pair<double,double> B{P2.first-P1.first, P2.second-P1.second};
        string dir = turnType(A,B);
        string street = Name[route[i]][route[i+1]];
        cout<<"  "<<dir<<" onto "<< (street.empty()?"<unnamed road>":street) <<endl;
    }

    cout<<"  Arrive at destination ("<<ex<<","<<ey<<")"<<endl;
    cout<<"Total distance = "<<dist<<endl;
}

// Function to quit the program
// Parameters: None.
// Return value: None.
// Written by: Khoi V.
void GraphMap::quit() {
    cout<<"Exiting... Thank you!"<<endl;
    exit(0);
}
