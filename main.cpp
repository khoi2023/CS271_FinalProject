/*
main.cpp
This file contains the main function for the CLI route planner program.
Written by: Khoi V.
*/
#include <iostream>
#include "CLI.hpp"

using namespace std;

int main() {
    // Welcome message and load the graph
    // The program prompts the user to enter a file name to load the graph
    cout << "Welcome to CLI route planner! (enter 'q' to quit)" << endl;
    GraphMap gm;
    while (!gm.load_file()) { /* retry */ }
    while (true) {
        // Prompt the user to enter start and end coordinates, then find the shortest path.
        gm.find_path();
    }
    return 0;
}