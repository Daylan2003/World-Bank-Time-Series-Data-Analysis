#ifndef TIMESERIES_H
#define TIMESERIES_H
#include "linked_list.h"

#include <string>



class TimeSeries {

    private:
        std::string countryName;
        std::string countryCode;
        std::string seriesName;
        std::string seriesCode;
        int* years;                 //This dynamically allocates an array for years
        double* data;               //This dynamically allocates an array for data
        int size;
        int capacity;

        //void resize(bool increase);

    public:
        TimeSeries();
        ~TimeSeries();
        TimeSeries(const TimeSeries& other);


        std::string getCountryName(); 
        std::string getCountryCode();
        std::string getSeriesName();
        std::string getSeriesCode();
        int getSize();
        int getCapacity();
        TimeSeries* next;   //This will be a pointer to the next node. First it is initialized to nullptr


        void addData(int year, double value);
        void updateData(int year, double value);
        void deleteData(int year, double value);
        void resizeArray(int newCapacity);
        double mean();
        void check_monotonic();
        void best_fit();
        void setSeriesInfo(const std::string& name, const std::string& code);
        bool load_all(std::string& filename, Linked_List giantCountryArray[], int& countryCount);
        bool load(std::string& filename, std::string& countryNameSearch, int i, Linked_List giantCountryArray[]);
        bool insert(std::string countryCode, std::string &filename, Linked_List giantCountryArray[]);
        bool loadForCountry(const std::string &filename, const std::string &countryNameSearch);
        bool loadFromLine(const std::string &line);
        void print() const;
};



#endif