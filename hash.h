#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>


typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0};
        std::vector<HASH_INDEX_T> temp;
        for (size_t m = 0; m < k.length(); m++)
        {
          temp.push_back(letterDigitToNumber(std::tolower(k[m])));

        }
        int group = 0;
        for (int i = static_cast<int>(temp.size()) - 1; i >= 0 && group < 5; group++){
          unsigned long long mult = 1;
          for (int j = 0; j < 6 && i >= 0; j++, i--) {
            w[4 - group] += temp[i] * mult;
            mult *= 36;
          }
    }
    HASH_INDEX_T ret = 0;
    for (int l = 0; l < 5; l++){
      ret += (rValues[l] * w[l]);
    }
    return ret;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        HASH_INDEX_T x = static_cast<int>(letter);
        if (47 < letter && 58 > letter){
          x -= 22;
        }else if (96 < x && x < 123){
          x -= 97;
        }
        return x;

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
