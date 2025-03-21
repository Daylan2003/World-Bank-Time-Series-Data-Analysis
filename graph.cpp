#include "graph.h"
#include "tree.h"
#include <iostream>
#include <string>

//The nodes of my graph will have country objects.
//If 2 nodes share a relation on at least one timeseries then they are connected via and edge.
//They are connected by an adjacency list or an adjacency matrix. 
//I will use an ajacency list, it will be a map of maps.  

//std::unordered_map<std::string, std::unordered_map<std::string, std::tuple<std::string, int, std::string>>> adjList;



// Constructor
Graph::Graph()
{}

// Destructor
Graph::~Graph() {}

void Graph::initializeNodes(Linked_List giantCountryArray[]) {
    int countryCount = 0;

    //I should clear my map first, in the even it has been initialized
    adjList.clear();

    //Initialize each node of my graph
    for (int i = 0; i < 512; i++) {
        if (giantCountryArray[i].countryName != "") {
            adjList[giantCountryArray[i].countryCode];
            countryCount++;
        }
    }
    //std::cout << countryCount << std::endl;
    /*int count = 1;
    for (const auto& pair : adjList) {

        std::cout << count << " " << pair.first << std::endl; 
        count++;
    }*/
}

//add giant country array to paramaters
void Graph::updateEdges(std::string seriesCode, int threshold, std::string relation, tree myTree, Linked_List giantCountryArray[]) {

    bool relationsAdded = false;
    std::tuple<std::string, int, std::string> myTuple(seriesCode, threshold, relation);
    

    //The tree is built so now I should call the find function for my binary tree
    //It will return an array of strings, which are the country codes.

    //std::vector<std::string> countryCodes = myTree.returnCountriesGraph(threshold, relation, giantCountryArray);
    myTree.findCountries(threshold, relation, giantCountryArray);

    if (relationsAdded) {
        std::cout << "success" << std::endl;    
    }
    else {
        std::cout << "failure" << std::endl;
    }
}


