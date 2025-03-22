#include "graph.h"
#include "tree.h"
#include <iostream>
#include <string>

//The nodes of my graph will have country objects.
//If 2 nodes share a relation on at least one timeseries then they are connected via and edge.
//They are connected by an adjacency list or an adjacency matrix. 
//I will use an ajacency list, it will be a map of maps.  

//std::unordered_map<std::string, std::unordered_map<std::string, std::tuple<std::string, int, std::string>>> adjList;
//std::map<Linked_List, std::map<Linked_List, std::vector<std::tuple<std::string, int, std::string>>>> adjList;




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
void Graph::updateEdges(std::string seriesCode, double threshold, std::string relation, tree &myTree, Linked_List giantCountryArray[]) {

    bool relationsAdded = false;
    int relationshipsAdded = 0;
    std::tuple<std::string, int, std::string> relationship(seriesCode, threshold, relation);
    

    //The tree is built so now I should call the find function for my binary tree
    //It will return an array of strings, which are the country codes.

    //This vector now has country codes. 
    std::vector<std::string> countryCodes = myTree.returnCountriesGraph(threshold, relation, giantCountryArray);



    //myTree.findCountries(threshold, relation, giantCountryArray);

    int count = 0;
    for (size_t i = 0; i < countryCodes.size(); i++) {
        count++;
        //std::cout << count << " " << countryCodes[i] << std::endl;
    }

    for (const auto& pair : adjList) {
        //std::cout << pair.first << std::endl; 

        std::string target = pair.first;

        auto it = std::find(countryCodes.begin(), countryCodes.end(), target);

        if (it != countryCodes.end()) {

            for (size_t i = 0; i < countryCodes.size(); i++) {
                if (countryCodes[i] != target) {

                    auto& relationsVec = adjList[target][countryCodes[i]];
                    
                    // Check to prevent duplicates
                    if (std::find(relationsVec.begin(), relationsVec.end(), relationship) == relationsVec.end()) {
                        relationsVec.push_back(relationship);
                        relationsAdded = true;
                        relationshipsAdded++;
                    }
                } 
            }
        }
        else {
            //break;
            continue;
        }
    }

    //std::cout << "Relationships added: " << relationshipsAdded << std::endl;

    if (relationsAdded) {
        std::cout << "success" << std::endl;    
    }
    else {
        std::cout << "failure" << std::endl;
    }
}


void Graph::printAdjacencyList() {
    // Iterate over each source node in the adjacency list.
    for (const auto& outerPair : adjList) {
        const std::string& source = outerPair.first;
        const auto& innerMap = outerPair.second;
        std::cout << "Source: " << source << std::endl;
        
        // Iterate over each destination node for this source.
        for (const auto& innerPair : innerMap) {
            const std::string& destination = innerPair.first;
            const auto& relations = innerPair.second;
            std::cout << "  Destination: " << destination << " -> ";
            
            // Iterate over all relations (tuples) for the edge.
            for (const auto& relation : relations) {
                // Unpack the tuple: (relation type, weight, extra info)
                std::cout << "(" 
                          << std::get<0>(relation) << ", "
                          << std::get<1>(relation) << ", "
                          << std::get<2>(relation) << ") ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl; // Extra line for readability between nodes.
    }
}
