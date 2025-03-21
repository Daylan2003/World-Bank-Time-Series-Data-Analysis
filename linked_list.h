#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <string>

class TimeSeries;

class Linked_List {

    private:
        

    public:
        Linked_List();
        ~Linked_List();
        TimeSeries* head;   //The head of my linked list. In the constuctor I will initialize it to nullptr.
        TimeSeries* tail; 

        std::string countryName;
        std::string countryCode;
        int index;
        int searches;
        bool occupied;

        

        void append(const TimeSeries& new_time_series); 
        void list();
        void print(std::string& seriesCode);
        void add(int year, double data, std::string& seriesCode);
        void update(int year, double data, std::string& seriesCode);
        void deleteSeries(std::string& seriesCode);
        double getMean(std::string& seriesCode);
        void biggestMean();
        void clearList();
        TimeSeries* getHead();

        std::string getCountryNameList();

        void printCountry();
        //Have to create a delete function
};
#endif