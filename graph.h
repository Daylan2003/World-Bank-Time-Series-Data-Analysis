#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <tuple>
#include "linked_list.h"
#include "tree.h"

class Graph {
private:

    //Here is the initialization of my graph. It will be a map of maps. 
    //The main map will have a country object as the key and a map as the value.
    //The inner map will have a country object as the key and a tuple of series code, threshold and relation
    std::unordered_map<std::string, std::unordered_map<std::string, std::tuple<std::string, int, std::string>>> adjList;

public:
    // Constructor
    Graph();

    // Destructor
    ~Graph();

    void initializeNodes(Linked_List giantCountryArray[]);
    void updateEdges(std::string seriesCode, int threshold, std::string relation, tree myTree, Linked_List giantCountryArray[]);
};

#endif 
