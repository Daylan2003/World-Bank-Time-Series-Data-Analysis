#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <map>
#include <vector>
#include <tuple>
#include <set>
#include <algorithm>
#include "linked_list.h"
#include "tree.h"

class Graph {
private:

    //Here is the initialization of my graph. It will be a map of maps. 
    //The main map will have a country object as the key and a map as the value.
    //The inner map will have a country object as the key and a tuple of series code, threshold and relation
    //These tuples will be stored in a vector however, as there may be multiple relations between two nodes.

    //std::unordered_map<std::string, std::unordered_map<std::string, std::tuple<std::string, int, std::string>>> adjList;
    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::tuple<std::string, int, std::string>>>> adjList;



public:
    // Constructor
    Graph();

    // Destructor
    ~Graph();

    void initializeNodes(Linked_List giantCountryArray[]);
    void updateEdges(std::string seriesCode, double threshold, std::string relation, tree &myTree, Linked_List giantCountryArray[]);
    void adjacent(std::string seriesCode, Linked_List giantCountryArray[]);

    void printAdjacencyList();
};

#endif 
