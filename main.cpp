#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <tuple>
#include "time_series.h"  
#include "linked_list.h"
#include "tree.h"
#include "hashing.h"
#include "graph.h"

int main() {

    //Here is my hashtable of Country Objects(Linked Lists)    
    Linked_List giantCountryArray[512];

    //This creates an instance of my graph
    Graph myGraph;
    TimeSeries series;  //This creates an instance of the TimeSeries Class (to be removed later)




    std::string command;
    bool treeExists = false;

    tree myTree;
    double min;
    double max;
    double range;
    int countryCount = 0;
   

    //These if else statements are for the commands for the design document which then activate the functions in my TimeSeries
    while (std::cin >> command) {
        

        /*
        CITATION: ChatGPT used to generate skeleton of if else statements for corresponding commands. I entered in the logig in these if else statements myself however
        */
        if (command == "LOAD") {


            std::string filename;
            std::cin >> filename;

            for (int i = 0; i < 512; i++) {
                giantCountryArray[i].countryName = "";
                giantCountryArray[i].occupied = false;
            }

            if (series.load_all(filename, giantCountryArray, countryCount)) {
                std::cout << "success" << std::endl;
            } else {
                std::cout << "failure" << std::endl;
            }

            

            //giantCountryArray[341].printCountry();
            //std::cout << countryCount << std::endl;
            //int counter = 1;

           // for (int i = 0; i < 512; i++) {
               //std::cout << counter << giantCountryArray[i].countryCode << giantCountryArray[i].countryName << std::endl;

               //std::cout << counter << giantCountryArray[i].getCountryNameList() <<std::endl;
               //counter++;
           // }

            
        }

        else if (command == "LIST") {
            std::string countryName;
            std::cin.ignore();
            std::getline(std::cin, countryName);
            //std::cout << countryName << std::endl;
            //giantCountryArray[0].list();
            bool countryFound = false;

            
            for (int i = 0; i < 512; i++) {
                //std::cout << giantCountryArray[i].getCountryNameList() << std::endl;
                if (giantCountryArray[i].getCountryNameList() == countryName) {
                    giantCountryArray[i].list();
                    countryFound = true;
                    break;
                }
            }
            if (!countryFound) {
                std::cout << "Country not found " << std::endl;
            }
        }

        else if (command == "RANGE") {
            std::string seriesCode;
            std::cin >> seriesCode;          
            int counter = 0;

            for (int i = 0; i < 512; i++) {

                if (giantCountryArray[i].getMean(seriesCode) > 0) {

                    if (i == 0) {
                        min = giantCountryArray[i].getMean(seriesCode);
                        max = giantCountryArray[i].getMean(seriesCode);
                    }

                    if (giantCountryArray[i].getMean(seriesCode) > max) {
                        max = giantCountryArray[i].getMean(seriesCode);
                    }

                    if (giantCountryArray[i].getMean(seriesCode) < min) {
                        min = giantCountryArray[i].getMean(seriesCode);
                    }

                }
                counter++;
                //std::cout << counter << " " << giantCountryArray[i].getMean(seriesCode) << std::endl;
            }
            std::cout << min << " " << max << std::endl;
            //std::cout << "Max is: " << max << std::endl;
            //std::cout << "Min is: " << min << std::endl;
        }

        else if (command == "BUILD") {
            std::string seriesCode;
            std::cin >> seriesCode; 
            treeExists = true;

            for (int i = 0; i < 512; i++) {

                if (giantCountryArray[i].countryName != "") {

                    if (giantCountryArray[i].getMean(seriesCode) > 0) {

                        if (i == 0) {
                            min = giantCountryArray[i].getMean(seriesCode);
                            max = giantCountryArray[i].getMean(seriesCode);
                        }
    
                        if (giantCountryArray[i].getMean(seriesCode) > max) {
                            max = giantCountryArray[i].getMean(seriesCode);
                        }
    
                        if (giantCountryArray[i].getMean(seriesCode) < min) {
                            min = giantCountryArray[i].getMean(seriesCode);
                        }
                    }
                }

                
                //std::cout << counter << " " << giantCountryArray[i].getMean(seriesCode) << std::endl;
            }

            range = max - min;
            //std::cout << "Range is: " << range << std::endl;

            myTree.build(seriesCode, min, max, giantCountryArray);
            std::cout << "success" << std::endl;
            //myTree.traverse();

            //for (int i = 0; i < 512; i++) {
            //    std::cout << giantCountryArray[i].countryName << " " << giantCountryArray[i].getMean(seriesCode) << std::endl;
            //}
        }

        else if (command == "FIND") {
            double number;
            std::cin >> number;
            std::string operation;
            std::cin >> operation;

            myTree.findCountries(number, operation, giantCountryArray);
        }

        else if (command == "DELETE") {
            std::string countryName;
            std::cin.ignore();
            std::getline(std::cin, countryName);

            myTree.deleteCountry(countryName);
        }

        else if (command == "LIMITS") {
            std::string operation;
            std::cin >> operation;

            myTree.limits(operation);
        }

        else if (command == "LOOKUP") {
            std::string countryCode;
            std::cin >> countryCode;

            lookup(countryCode, giantCountryArray);
        }
        //Here is what happens when remove is called. 
        //All calcultions happen here since the instance for my hashtable is created in the main file
        else if (command == "REMOVE") {
            std::string countryCode;
            std::cin >> countryCode;
            std::string countryName;

            bool countryFound = false;

            int W = hash1(countryCode);
            int firstHashIndex = W % 512;
            int secondHashIndex = hash2(W);
            int i = 0;
            int currentHashIndex;

            while (i < 512) {
                currentHashIndex = (firstHashIndex + i * secondHashIndex) % 512;
                if (giantCountryArray[currentHashIndex].countryCode == countryCode) {
                    countryName = giantCountryArray[currentHashIndex].countryName;
                    //if the tree exists, delete the country from the tree
                    if (treeExists) {
                        myTree.removeCountry(countryName);
                    }
                    giantCountryArray[currentHashIndex].clearList();
                    giantCountryArray[currentHashIndex].countryCode = "";
                    giantCountryArray[currentHashIndex].countryCode = "";
                    countryFound = true;
                }

                i++; // Increment the loop counter
            }

            if (countryFound) {
                std::cout << "success" << std::endl;
            }
            else{
                std::cout << "failure" << std::endl;
            }
        }

        else if (command == "INSERT") {
            std::string countryCode;
            std::cin >> countryCode;

            std::string fileName;
            std::cin >> fileName;
            bool existsInArray = false;

            int W = hash1(countryCode);
            int firstHashIndex = W % 512;
            int secondHashIndex = hash2(W);
            int i = 0;
            int currentHashIndex;

            while (i < 512) {
                currentHashIndex = (firstHashIndex + i * secondHashIndex) % 512;
                if (giantCountryArray[i].countryCode == countryCode) {
                    existsInArray = true;
                    break;
                }

                i++; // Increment the loop counter
            }

            if (!existsInArray) {
                series.insert(countryCode, fileName, giantCountryArray);  
                std::cout << "success" << std::endl;  
            }
            else {
                std::cout << "failure" << std::endl;
            }

        }

        else if (command == "INITIALIZE") {

            //Add country objects to my map
            myGraph.initializeNodes(giantCountryArray);

            std::cout << "success" << std::endl;
        }

        else if (command == "UPDATE_EDGES") {
           
            std::string seriesCode;
            int threshold;
            std::string relation;

            std::cin >> seriesCode;
            std::cin >> threshold;
            std::cin >> relation;
           
            //first a binary tree has to be built. 
            //Then using my find function relationships will be determined. 
            //update the adjacency matrix
        }

        else if (command == "ADJACENT") {

        }

        else if (command == "PATH") {

        }

        else if (command == "RELATIONSHIPS") {

        }
     
        /*else if (command == "PRINT") {
            std::string seriesCode;
            std::cin >> seriesCode;
            linkedList.print(seriesCode);
        }*/

        
        /*else if (command == "ADD") {
            int year;
            double data;
            std::string seriesCode;
            std::cin >> seriesCode;
            std::cin >> year;
            std::cin >> data;
            linkedList.add(year, data, seriesCode);
        }*/

       
        /*else if (command == "UPDATE") {
            int year;
            double data;
            std::string seriesCode;
            std::cin >> seriesCode;
            std::cin >> year;
            std::cin >>data;
            linkedList.update(year, data, seriesCode);
        }*/

        
        else if (command == "MEAN") {
            series.mean();
        }

      
        else if (command == "MONOTONIC") {
            series.check_monotonic();
        }

        
        else if (command == "FIT") {
            series.best_fit();
        }

        /*else if (command == "DELETE") {
            std::string seriesCode;
            std::cin >> seriesCode;
            linkedList.deleteSeries(seriesCode);
        }*/

        /*else if (command == "BIGGEST") {
            linkedList.biggestMean();
        }*/

        
        else if (command == "EXIT") {       //Program exits on running this so that works
            break;
        }
    }
    return 0;
}


