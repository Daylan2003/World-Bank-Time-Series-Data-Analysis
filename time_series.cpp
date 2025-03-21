#include "time_series.h"
#include "linked_list.h"
#include "hashing.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>


//This will be my constructor
TimeSeries::TimeSeries()   
    : countryName(""), countryCode(""), seriesName(""), seriesCode(""), capacity(2), size(0), next(nullptr) {
    years = new int[capacity];
    data = new double[capacity];
}


//This will be my destructor
TimeSeries::~TimeSeries() {
        delete[] years;
        delete[] data;

        years = nullptr;
        data = nullptr;
}

//This is meant to be my copy constructor
TimeSeries::TimeSeries(const TimeSeries& other)
    : countryName(other.countryName), countryCode(other.countryCode),
      seriesName(other.seriesName), seriesCode(other.seriesCode),
      capacity(other.capacity), size(other.size), next(nullptr) {  // Ensure next is reset

    years = new int[capacity];
    data = new double[capacity];

    for (int i = 0; i < size; ++i) {
        years[i] = other.years[i];
        data[i] = other.data[i];
    }
}




//getters (in case they will be needed in future parts of this project)
/*
    CITATION: ChatGPT used to create getter functions
*/
std::string TimeSeries::getCountryName() { return countryName; }
std::string TimeSeries::getCountryCode() { return countryCode; }
std::string TimeSeries::getSeriesName() { return seriesName; }
std::string TimeSeries::getSeriesCode() { return seriesCode; }
int TimeSeries::getSize() { return size; }
int TimeSeries::getCapacity() { return capacity; }


void TimeSeries::resizeArray(int newCapacity) {

    //if the capacity is less than 2, set the capacity to be 2
    if (newCapacity < 2) {
        newCapacity = 2;
    }

    //New dynamic array for years
    int* newArrayYear = new int[newCapacity];

    for (int i = 0; i < size; i++) {
        newArrayYear[i] = years[i];
    }

    //Delete old array
    delete[] years;
    years = newArrayYear;   //Set array to new array


    //Do the same as what I did up above but for my array of data
    double* newArrayData = new double[newCapacity];

    for (int i = 0; i < size; i++) {
        newArrayData[i] = data[i];
    }

    delete[] data;
    data = newArrayData;

    capacity = newCapacity;
}

void TimeSeries::addData(int year, double value) {

 
    for (int i = 0; i < size; i++) {
        //If yeah already exists it should print failure
        if (years[i] == year)
        {
            std::cout << "failure" << std::endl;
            return;
        }
    }

    if (size == capacity) {
        resizeArray(capacity * 2);
    }

    //This is the set of code to find the correct insert position when we want to add a new year
    int insertPos = size;
    for (int i = 0; i < size; i++) {
        if (years[i] > year) {
            insertPos = i;
            break;
        }
    }

    //We need to shift data to the right to make room for the year we want to insert
    for (int i = size; i > insertPos; i--) {
        years[i] = years[i - 1];
        data[i] = data[i - 1];
    }

    years[insertPos] = year;
    data[insertPos] = value;
    size++;

    //Print success if it was done correctly
    std::cout << "success" << std::endl;

    //This is the calculations for making the dynamic array smaller
    if (size <= capacity / 4 && capacity > 2) {
        resizeArray(capacity / 2);
    }
}

void TimeSeries::updateData(int year, double value) {

    //To update data which already exists
    for (int i = 0; i < size; i++) {
        //This if statement basically checks if the year already exists in the Time Series
        if (years[i] == year) {  
            data[i] = value;
            std::cout << "success" << std::endl; 
            return; 
        } 
    }
    //If it does not exist then we should print failure
    std::cout << "failure" << std::endl;
}

//This may be for future parts of the project. A delete function
void TimeSeries::deleteData(int year, double value) {

}


double TimeSeries::mean() {
    //If there is no data this function simply returns failure
    if (size == 0) {
        //std::cout << "failure" << std::endl;
        return -1;
    }

    double total = 0.0;

    //Calculations for the total value
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (data[i] != -1)
        {
            total += data[i];
        }
        count++;
    }

    if (count == 0) {
        return -1;  
    }
    //We output the mean value here
    //std::cout << "mean is " << (total / size) << std::endl;
    double mean = (total / size);
    //mstd::cout << "sum is: " << total << " size is: " << size << " mean is: " << mean << std::endl;
    return mean;
}

void TimeSeries::check_monotonic() {
    //std::cout << size << std::endl;
    if (size == 0) {
        std::cout << "failure" << std::endl;
        return;
    }

    bool isIncreasing = true;
    bool isDecreasing = true;

    for (int i = 0; i < size - 1; i++){

        if (data[i] < data[i + 1]) {
            isDecreasing = false;
        }
        if (data[i] > data[i + 1]) {
            isIncreasing = false;
        }
    }

    if (isIncreasing || isDecreasing) {
        std::cout << "series is monotonic" << std::endl;
    } else {
        std::cout << "series is not monotonic" << std::endl;
    }
}

void TimeSeries::best_fit() {
    //Calculations to find the slope and y intercept as according to the design document
    if (size == 0) {
       int m = 0.0;
       int b = 0.0;
       std::cout << "failure" << std::endl;
       return;
    }

    double sumX = 0.0; 
    double sumY = 0.0; 
    double sumXY = 0.0; 
    double sumX2 = 0.0;

    for (int i = 0; i < size; i++) {
        if (data[i] != -1) {
            sumX += years[i];
            sumY += data[i];
            sumXY += years[i] * data[i];
            sumX2 += years[i] * years[i];
        }
    }


    int m = (size * sumXY - sumX * sumY) / (size * sumX2 - sumX * sumX);
    int b = (sumY - m * sumX) / size;

    std::cout << "slope is " << m << " intercept is " << b << std::endl;

    return;
}

//This function helps with initializing an empty Time Series
void TimeSeries::setSeriesInfo(const std::string& name, const std::string& code) {
    seriesName = name;
    seriesCode = code;
}


/*
    CITATION: ChatGPT used to understand what the getline() function does and returns to the user
*/

//Needs a function which stores the current country and the previous country
//It should iterate through the timeseries, and when a new country is found it should call the load function again.
//It should do this until it reaches the end of the timeseries.
//Load function correctly loads all data into a timeseries when given a country
//The load function should also add the timeseries into an array



bool TimeSeries::loadFromLine(const std::string &line) {
    // Reset the current object's data.
    delete[] years;
    delete[] data;
    capacity = 2;
    size = 0;
    years = new int[capacity];
    data = new double[capacity];
    
    std::stringstream s_stream(line);
    
    // Parse the first four fields.
    if (!std::getline(s_stream, countryName, ',')) return false;
    if (!std::getline(s_stream, countryCode, ',')) return false;
    if (!std::getline(s_stream, seriesName, ',')) return false;
    if (!std::getline(s_stream, seriesCode, ',')) return false;
    
    int year = 1960;
    std::string valueString;
    while (std::getline(s_stream, valueString, ',')) {
        double value = std::stod(valueString);
        if (value != -1) {
            if (size == capacity) {
                resizeArray(capacity * 2);
            }
            years[size] = year;
            data[size] = value;
            size++;
        }
        year++;
    }
    // Optionally shrink the array if too sparse.
    if (size <= capacity / 4 && capacity > 2) {
        resizeArray(capacity / 2);
    }
    return true;
}


//My load function to load all data
bool TimeSeries::load_all(std::string &filename, Linked_List giantCountryArray[], int &countryCount) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false; 
    }
    
    std::string line;
    std::string currentCountry = "";
    std::string currentCountryCode = "";
    int currentHashIndex = -1;
    
    
    while (std::getline(file, line)) {
        TimeSeries temp;
        
        // Parse the line into the temporary TimeSeries.
        if (!temp.loadFromLine(line)) {
            continue;  // Skip malformed lines.
        }
        
        // If the country has changed, update our current index.
        if (temp.getCountryName() != currentCountry) {
            currentCountry = temp.getCountryName();
            currentCountryCode = temp.getCountryCode();

            int W = hash1(currentCountryCode);
            int firstHashIndex = W % 512;
            int secondHashIndex = hash2(W);
            bool locationFree = false;
            int i = 0;
         
            //std::cout << currentCountryCode << ": " << firstHashIndex << "       " <<  secondHashIndex << std::endl;

            
            //Here is my hash calculations for loading all data into their necessary places
            while (!locationFree) {

                currentHashIndex = (firstHashIndex + i*secondHashIndex) % 512;

                if (giantCountryArray[currentHashIndex].countryCode == "") {
                    locationFree = true;
                }
                else {
                    i++;
                }
            }

                     // Move to the next linked list.
            countryCount++;
            giantCountryArray[currentHashIndex].clearList(); // Clear any existing data if needed.
            giantCountryArray[currentHashIndex].countryName = currentCountry;
            giantCountryArray[currentHashIndex].countryCode = currentCountryCode;
            giantCountryArray[currentHashIndex].occupied = true;
            giantCountryArray[currentHashIndex].index = currentHashIndex;
            giantCountryArray[currentHashIndex].searches = i+1;
        }
        
        // Append this temporary TimeSeries to the current country's linked list.
        giantCountryArray[currentHashIndex].append(temp);
    }
    
    file.close();
    return true;
}


//This is my insert function. It works very simmilar to my load function except it only adds all timeseries for a single country
bool TimeSeries::insert(std::string countryCode, std::string &filename, Linked_List giantCountryArray[]) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false; 
    }
    
    std::string line;
    int currentHashIndex = -1;
    bool initialized = false;  // Flag to indicate that we've already initialized the slot for this country.
    
    while (std::getline(file, line)) {
        TimeSeries temp;
        
        // Parse the line into a temporary TimeSeries.
        if (!temp.loadFromLine(line)) {
            continue;  // Skip malformed lines.
        }
        
        // Process only lines with the given country code.
        if (temp.getCountryCode() != countryCode)
            continue;
        
        // For the first matching line, compute the hash index and initialize the slot.
        if (!initialized) {
            int W = hash1(countryCode);
            int firstHashIndex = W % 512;
            int secondHashIndex = hash2(W);
            bool locationFree = false;
            int i = 0;
            
            //Here is the calculations for inserting data to my hash table using the hash calculationd
            while (!locationFree) {
                currentHashIndex = (firstHashIndex + i * secondHashIndex) % 512;
                if (giantCountryArray[currentHashIndex].countryCode == "") {
                    locationFree = true;
                } else {
                    i++;
                }
            }
            
            // Initialize the linked list slot for this country.
            giantCountryArray[currentHashIndex].clearList(); // Clear any existing data.
            giantCountryArray[currentHashIndex].countryName = temp.getCountryName();
            giantCountryArray[currentHashIndex].countryCode = countryCode;
            giantCountryArray[currentHashIndex].index = currentHashIndex;
            giantCountryArray[currentHashIndex].searches = i+1;
            initialized = true;
        }
        
        // Append this temporary TimeSeries to the linked list for the given country.
        giantCountryArray[currentHashIndex].append(temp);
    }
    
    file.close();
    return initialized;  // Returns true if at least one matching country was inserted.
}






void TimeSeries::print() const {
    bool hasValidData = false;
    //This for loop essentially allows us to print the data which we have read from our csv file
    for (int i = 0; i < size; ++i) {
        if (data[i] != -1) { 
            if (hasValidData) {
                std::cout << " "; 
            }
            std::cout << "(" << years[i] << "," << data[i] << ")";
            hasValidData = true;
        }
    }

    if (!hasValidData) {
        std::cout << "failure";  //If I enter an incorrect filename in, this prints which is correct
    }

    std::cout << std::endl;
}

