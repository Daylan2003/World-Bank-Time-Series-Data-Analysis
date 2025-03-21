#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <vector>
#include "linked_list.h"
#include "time_series.h"

class Node {
public:
    std::string countries[512];  // Fixed-size array for storing country names
    double min;
    double max;

    
    Node* left;
    Node* right;
    

    Node();  // Constructor
    ~Node();
};

class tree {
    public:
        std::string seriesCodeTree;
        double initialMin;  // Added to record the initial min.
        double initialMax;  // Added to record the initial max.

        tree();
        ~tree();
        
        void build(std::string& seriesCode, double min, double max, Linked_List giantCountryArray[]);
        void findCountries(double mean, std::string& operation, Linked_List giantCountryArray[]);
        std::vector<std::string> returnCountriesGraph(double target, std::string& operation, Linked_List giantCountryArray[]);
        void traverse();
        void limits(std::string& condition);
        void deleteCountry(const std::string &country);
        void removeCountry(const std::string &country);
    
    private:
        Node* root;
        Node* buildTree(std::string& seriesCode, double min, double max, Linked_List giantCountryArray[]);
        Node* deleteCountryHelper(Node* node, const std::string &country, bool &found);
        Node* getLimitLeaf(const std::string& condition);
        void printTree(Node* node); 
        void traverseTree(Node* node);
        void clearTree(Node* node);
    };

#endif  // TREE_H

