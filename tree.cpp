#include "tree.h"
#include <vector>
#include <queue>

// Node ConstructorBUIL
Node::Node() : min(0), max(0), left(nullptr), right(nullptr) {
    for (int i = 0; i < 512; i++) {
        countries[i] = "";  // Initialize array with empty strings
    }
}

Node::~Node() {
    
}

// Tree Constructor
tree::tree() : root(nullptr) {}


tree::~tree() {
    clearTree(root);
}

// Helper: Recursively delete nodes in the existing tree.
void tree::clearTree(Node* node) {
    if (!node)
        return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

// Recursively build the binary tree.
Node* tree::buildTree(std::string& seriesCode, double min, double max, Linked_List giantCountryArray[]) {
    if (min >= max) {
        return nullptr; 
    }
    
    // Allocate a new node and initialize its range.
    Node* node = new Node();
    node->min = min;
    node->max = max;
    int index = 0;

    // Iterate through giantCountryArray (each element is a linked list for a country)
    for (int i = 0; i < 512; i++) {
        TimeSeries* current = giantCountryArray[i].head; 
        while (current != nullptr) { 
            if (current->getSeriesCode() == seriesCode) { 
                double meanValue = current->mean();         

                // If the data is invalid (-1), set the mean to 0.
                if (meanValue == -1) {
                    meanValue = 0;
                }

                // If the mean falls within the current range, store the country name.
                if (meanValue >= min && meanValue <= max) {    
                    if (index < 512) { // Ensure we don't overflow the countries array
                        node->countries[index] = giantCountryArray[i].countryName;
                        index++;
                    }
                }
                break; // Found the series code; move to the next country.
            }
            current = current->next;
        }
    }
    
    // Tolerance to prevent infinite splitting if the range is extremely small.
    const double epsilon = 1e-3;
    
   
    if (index <= 1 || (max - min) < epsilon) {
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }
    
    // Otherwise, split the range into two halves.
    double mid = (min + max) / 2.0;
    node->left = buildTree(seriesCode, min, mid, giantCountryArray);
    node->right = buildTree(seriesCode, mid, max, giantCountryArray);

    return node;
}

void tree::build(std::string& seriesCode, double min, double max, Linked_List giantCountryArray[]) {
    // Clear any existing tree.
    if (root != nullptr) {
        clearTree(root);
        root = nullptr;
    }
    
    // Initialize the seriesCodeTree attribute with the provided series code.
    seriesCodeTree = seriesCode;
    
    // Iterate through giantCountryArray to check for invalid data.
    for (int i = 0; i < 512; i++) {
        double mean = giantCountryArray[i].getMean(seriesCode);
        if (mean == -1) { // Found invalid data
            min = 0;
            break; // Only need to update once.
        }
    }
    
    // Build the new tree with the (possibly updated) min.
    root = buildTree(seriesCode, min, max, giantCountryArray);
}

// Finds the leaf node with the highest max that is still less than target.
void tree::findCountries(double target, std::string& operation, Linked_List giantCountryArray[]) {
    bool found = false;

    if (root == nullptr) {
        std::cout << "failure" << std::endl;
        return;
    }

    // Iterate over all stored countries in the root node
    int count = 1;
    for (int i = 0; i < 512; i++) {
        if (!root->countries[i].empty()) { // Check if the country slot is used
            for (int j = 0; j < 512; j++) { // Search for the country in giantCountryArray
                if (giantCountryArray[j].countryName == root->countries[i]) {
                    double mean = giantCountryArray[j].getMean(seriesCodeTree);

                    // Convert invalid mean (-1) to 0.
                    if (mean == -1) {
                        mean = 0;
                    }

                    // Compute the absolute difference manually.
                    double diff = (mean - target) < 0 ? -(mean - target) : (mean - target);

                    // Compare mean value based on the operation.
                    if ((operation == "less" && mean < target) ||
                        (operation == "greater" && mean > target) ||
                        (operation == "equal" && diff <= 1e-3)) {

                        if (found)
                            //std::cout << " ";
                        //std::cout << giantCountryArray[j].countryName;
                        count++;
                        std::cout << count << " " << giantCountryArray[j].countryCode << std::endl;
                        found = true;
                    }
                    break; // Found the matching country, move to the next.
                }
            }
        }
    }
    
    if (!found) {
        std::cout << std::endl;
    }
    else {
        std::cout << std::endl;
    }
}


Node* tree::deleteCountryHelper(Node* node, const std::string &country, bool &found) {
    if (!node)
        return nullptr;


    
    // First, check the current node's countries array.
    bool removedFromThisNode = false;
    for (int i = 0; i < 512; i++) {
        if (node->countries[i] == country) {
            node->countries[i] = "";  // Remove the country.
            removedFromThisNode = true;
        }
    }
    if (removedFromThisNode)
        found = true;
    
    // Then, recursively process the left and right subtrees.
    node->left  = deleteCountryHelper(node->left, country, found);
    node->right = deleteCountryHelper(node->right, country, found);
    
    // After processing children, if this node is a leaf (no children) and its array is empty, delete it.
    if (node->left == nullptr && node->right == nullptr) {
        bool empty = true;
        for (int i = 0; i < 512; i++) {
            if (!node->countries[i].empty()) {
                empty = false;
                break;
            }
        }
        if (empty) {
            delete node;
            return nullptr;
        }
    }
    
    return node;
}

void tree::deleteCountry(const std::string &country) {
    // If no tree exists, output "failure".
    if (root == nullptr) {
        std::cout << "failure" << std::endl;
        return;
    }
    
    bool found = false;
    root = deleteCountryHelper(root, country, found);
    
    if (found)
        std::cout << "success" << std::endl;
    else
        std::cout << "failure" << std::endl;
}

void tree::removeCountry(const std::string &country) {
    // If no tree exists, output "failure".
    if (root == nullptr) {
        return;
    }
    bool found = false;
    
    root = deleteCountryHelper(root, country, found);
}


Node* tree::getLimitLeaf(const std::string& condition) {
    if (root == nullptr)
        return nullptr;
    
    Node* current = root;
    if (condition == "lowest") {
        // Traverse to the leftmost leaf.
        while (current->left != nullptr)
            current = current->left;
    }
    else if (condition == "highest") {
        // Traverse to the rightmost leaf.
        while (current->right != nullptr)
            current = current->right;
    }
    else {
        // Invalid condition.
        return nullptr;
    }
    return current;
}

//outputs the countries stored in the appropriate leaf.
void tree::limits(std::string& condition) {
    Node* leaf = getLimitLeaf(condition);
    if (leaf == nullptr) {
        std::cout << "failure" << std::endl;
        return;
    }
    
    bool first = true;
    // Iterate through the countries array in the leaf node.
    for (int i = 0; i < 512; i++) {
        if (!leaf->countries[i].empty()) {
            if (!first)
                std::cout << " ";
            std::cout << leaf->countries[i];
            first = false;
        }
    }
    std::cout << std::endl;
}


//I made this function to make sure my tree was being built correctly
//It traverses the tree from top to down, left to right.
void tree::traverseTree(Node* node) {
    if (!node)
        return;

    std::queue<Node*> q;
    q.push(node);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        // Print the current node's range and countries.
        std::cout << "Node Range: [" << current->min << ", " << current->max << "): ";
        bool first = true;
        for (int i = 0; i < 512; i++) {
            if (!current->countries[i].empty()) {
                if (!first)
                    std::cout << " ";
                std::cout << current->countries[i];
                first = false;
            }
        }
        std::cout << std::endl;

        // Push left and right children into the queue (left first, then right).
        if (current->left)
            q.push(current->left);
        if (current->right)
            q.push(current->right);
    }
}


// Public function: start the traversal from the root.
void tree::traverse() {
    traverseTree(root);
}


// Assuming the rest of your tree class and Linked_List are defined.

std::vector<std::string> tree::returnCountriesGraph(double target, std::string& operation, Linked_List giantCountryArray[]) {
    bool found = false;
    std::vector<std::string> countryCodes;  // dynamic array of strings

    if (root == nullptr) {
        //std::cout << "failure" << std::endl;
        return countryCodes; // returns an empty vector
    }

    // Iterate over all stored countries in the root node
    for (int i = 0; i < 512; i++) {
        if (!root->countries[i].empty()) { // Check if the country slot is used
            for (int j = 0; j < 512; j++) { // Search for the country in giantCountryArray
                if (giantCountryArray[j].countryName == root->countries[i]) {
                    double mean = giantCountryArray[j].getMean(seriesCodeTree);

                    // Convert invalid mean (-1) to 0.
                    if (mean == -1) {
                        mean = 0;
                    }

                    // Compute the absolute difference manually.
                    double diff = (mean - target) < 0 ? -(mean - target) : (mean - target);

                    // Compare mean value based on the operation.
                    if ((operation == "less" && mean < target) ||
                        (operation == "greater" && mean > target) ||
                        (operation == "equal" && diff <= 1e-3)) {

                        if (found)
                        //std::cout << giantCountryArray[j].countryCode << std::endl;
                        countryCodes.push_back(giantCountryArray[j].countryCode);
                        found = true;
                    }
                    break; // Found the matching country, move to the next.
                }
            }
        }
    }
    return countryCodes; // return the vector of country codes
}
