#include "hashing.h"
#include <fstream>
#include <sstream>

int m = 512;


//Here is my function for the first hash calculation. 
int hash1(std::string countryCode) {
        int hashValue;

        //std::cout << countryCode[0] << countryCode[1] << countryCode[2] << std::endl;
        hashValue = (static_cast<int>(countryCode[0]) - 'A') * 26 * 26 
                  + (static_cast<int>(countryCode[1]) - 'A') * 26
                  + (static_cast<int>(countryCode[2]) - 'A');  
        
        return hashValue;
}

//Here is my function for the second has calculation
int hash2(int W) {
    int x = (W / m) % m;
    if (x % 2 == 0) {
        return x + 1;
    } else {
        return x;
    }
}


//This s my lookup function. It uses hashing to look for the country in my array.
bool lookup(std::string lookupCountryCode, Linked_List giantCountryArray[]) {

    int W = hash1(lookupCountryCode);
    int firstHashIndex = W % 512;
    int secondHashIndex = hash2(W);
    int i = 0;
    int currentHashIndex;

    while (i < 512) {
        currentHashIndex = (firstHashIndex + i * secondHashIndex) % 512;
    
        if (lookupCountryCode == giantCountryArray[currentHashIndex].countryCode) {
            std::cout << "index " << giantCountryArray[currentHashIndex].index 
                      << " searches " << giantCountryArray[currentHashIndex].searches 
                      << std::endl;
            return true;
        }
        i++; // Increment the loop counter
    }

    std::cout << "failure" << std::endl;
    return false;
}
    






