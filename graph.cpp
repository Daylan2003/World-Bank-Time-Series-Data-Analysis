#include "graph.h"
#include "tree.h"
#include "hashing.h"
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
    int countriesEdited = 0;

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
            countriesEdited++;

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
    //std::cout << "Countries edited: " << countriesEdited << std::endl;

    if (relationsAdded) {
        std::cout << "success" << std::endl;    
    }
    else {
        std::cout << "failure" << std::endl;
    }
}

void Graph::adjacent(std::string seriesCode, Linked_List giantCountryArray[]) {
    std::string targetCountry = seriesCode;
    std::set<std::string> adjacentCountries;

    // Check if the target country exists in the adjacency list
    auto it = adjList.find(targetCountry);
    if (it == adjList.end()) {
        std::cout << "failure" << std::endl;
        return;
    }

    // Get the inner map and check if it's empty
    const auto& innerMap = it->second;
    if (innerMap.empty()) {
        std::cout << "none" << std::endl;
        return;
    }

    // Add keys of the inner map to the set
    for (const auto& innerPair : innerMap) {
        adjacentCountries.insert(innerPair.first);
    }

    // Print the adjacent countries
    for (const auto& country : adjacentCountries) {
        // Use the country (a string representing a country code) for hashing.
        int W = hash1(country);            // hash1 should accept a std::string.
        int firstHashIndex = W % 512;
        int secondHashIndex = hash2(W);      // hash2 uses the hash value to compute a second index.
        int i = 0;
        int currentHashIndex;
        bool found = false;

        // Use double hashing to locate the country in giantCountryArray.
        while (i < 512) {
            currentHashIndex = (firstHashIndex + i * secondHashIndex) % 512;
            if (giantCountryArray[currentHashIndex].countryCode == country) {
                std::cout << giantCountryArray[currentHashIndex].countryName << " ";
                found = true;
                break;
            }
            i++; // Increment the probe counter.
        }
    
}
std::cout << std::endl;
}
