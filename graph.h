#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>

class Graph {
private:
    std::unordered_map<int, std::vector<int>> adjList; // Adjacency list representation

public:
    // Constructor
    Graph();

    // Destructor
    ~Graph();
};

#endif // GRAPH_H
