#include "graph.h"
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


    for (int i = 0; i < 512; i++) {
        if (giantCountryArray[i].countryName != "") {
            adjList[giantCountryArray[i].countryCode];
            countryCount++;
        }
    }
    //std::cout << countryCount << std::endl;

    int count = 1;
    for (const auto& pair : adjList) {

        //std::cout << count << " " << pair.first << std::endl; 
        count++;
    }
}


