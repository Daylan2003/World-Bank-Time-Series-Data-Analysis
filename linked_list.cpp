#include <iostream>
#include "linked_list.h"
#include "time_series.h"

//Constructor for my linked list
Linked_List::Linked_List()
    : head(nullptr), tail(nullptr)
    {
    }

//Destructor for my linked list
Linked_List::~Linked_List() {
        TimeSeries* current = head;
        while (current != nullptr) {
            TimeSeries* next = current->next;  
            delete current;                    
            current = next;     
        }    
}




//A get hehad function. Used mainly for testing and debuggging
TimeSeries* Linked_List::getHead() {
    return head;
}

std::string Linked_List::getCountryNameList() { return countryName; }




// My function to add a new timeseries object to my linked list
void Linked_List::append(const TimeSeries& new_time_series) {

    TimeSeries* new_node = new TimeSeries(new_time_series);

    if (head == nullptr) {
        head = new_node;
        tail = new_node;  // Update tail
    } else {
        tail->next = new_node;
        tail = new_node;  // Move tail to the new last node
    }
}


//Function to list out the series name of my linked list. 
//First it prints the country name and code and then it lists out all the series names of the linked list
void Linked_List::list() {
    TimeSeries* current = head;

    std::cout << current->getCountryName() << " " << current->getCountryCode() << " ";
    while (current != nullptr) {
        std::cout << current->getSeriesName() << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

//I create this function to help clear my linked list in the load function
void Linked_List::clearList() {
    while (head != nullptr)
    {
        TimeSeries* current = head;
        head = head->next;
        delete current;
    }
    tail = nullptr;
}

//Essentially searches for the series code and if it is present in my linked list, it prints out the corresponding years and values.
void Linked_List::print(std::string& seriesCode) {
    std::string seriesCodeInput = seriesCode;
    bool isFound = false;

    TimeSeries* current = head;
    while (current != nullptr) {
        if (current->getSeriesCode() == seriesCodeInput) {
            current->print();
            isFound = true;
            break;
        }
        current = current->next;
    }
    if (!isFound) {
        std::cout << "failure" << std::endl;  // If no matching seriesCode is found
    }
}

//A print country function for debugging
void Linked_List::printCountry() {
    TimeSeries* current = head; // Assuming 'head' is the first node of the linked list
    int index = 1; // Start numbering from 1

    while (current != nullptr) {
        std::cout << index << ". Country: " << getCountryNameList() 
                  << "Country Code: " << current->getCountryCode()
                  << ", Series: " << current->getSeriesName() << std::endl;
        current = current->next;
        index++; // Increment counter
    }
}

//Searches for the series code and if it is present, connect to the add function from project 1
void Linked_List::add(int year, double data, std::string& seriesCode) {
    std::string seriesCodeInput = seriesCode;
    bool isFound = false;

    TimeSeries* current = head;
    while (current != nullptr) {
        if (current->getSeriesCode() == seriesCodeInput) {
            current->addData(year, data);
            isFound = true;
            break;
        }
        current = current->next;
    }
    if (!isFound) {
        std::cout << "failure" << std::endl;  // If no matching seriesCode is found
    }
}

//Searches for the series code and if it is present, connect to the update function from project 1
void Linked_List::update(int year, double data, std::string& seriesCode) {
    std::string seriesCodeInput = seriesCode;
    bool isFound = false;

    TimeSeries* current = head;
    while (current != nullptr) {
        if (current->getSeriesCode() == seriesCodeInput) {
            current->updateData(year, data);
            isFound = true;
            break;
        }
        current = current->next;
    }
    if (!isFound) {
        std::cout << "failure" << std::endl;  // If no matching seriesCode is found
    }
}

//My function to delete a series from the linked list.
//Uses the series code to do so. 
//If the series code is present, it itereates to that node, lets the previous node connect to the next node and then 
//we get rid of the node we want to delete.
void Linked_List::deleteSeries(std::string& seriesCode) {
    std::string seriesCodeInput = seriesCode;
    bool isFound = false;

    TimeSeries* current = head;
    TimeSeries* previous = nullptr;
    while (current != nullptr) {
        if (current->getSeriesCode() == seriesCodeInput) {
            isFound = true;
            if (current == head) {
                head = head->next;
                if (head == nullptr) {
                    tail = nullptr;
                }
            }
            else {
                previous->next = current->next;
                if (current == tail) {
                    tail = previous;
                }
            }

            delete current;
            std::cout << "success" << std::endl;
            return;
        }
        previous = current;
        current = current->next;
    }
    if (!isFound) {
        std::cout << "failure" << std::endl;  // If no matching seriesCode is found
    }
}


//My function to find the biggest mean.
//Uses the mean function from project 1.
//Iterates from the start of the series and whatever is the biggest found mean is stored as my "largest mean" value
//Then all we do is output the series code with this largest value.
void Linked_List::biggestMean() {
    double largest = -1;
    std::string largestSeriesCode;
    bool hasValidData = false;

    TimeSeries* current = head;
    while (current != nullptr) {
        double seriesMean = current->mean();
        //std ::cout << seriesMean << std::endl;

        if (seriesMean != -1) {
            hasValidData = true;

            if (seriesMean > largest) {
            largest = seriesMean;
            largestSeriesCode = current->getSeriesCode();
            }
        }
        current = current->next;    
    }
    if (hasValidData) {
        std::cout << largestSeriesCode << std::endl;        
    } else {
        std::cout << "failure" << std::endl;
    }
    
}

double Linked_List::getMean(std::string& seriesCode) {
    std::string seriesCodeInput = seriesCode;
    bool isFound = false;
    double mean = 0.0;
    
    TimeSeries* current = head;
    while (current != nullptr) {

       if (current->getSeriesCode() == seriesCodeInput) {
            mean = current->mean();
            return mean;
       }
       current = current->next; 
    }
    return mean;
}